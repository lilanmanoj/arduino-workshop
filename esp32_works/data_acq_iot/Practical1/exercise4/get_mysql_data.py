import mysql.connector
from mysql.connector import Error
import matplotlib.pyplot as plt
import numpy as np

plt.close("all")
try:
    mydb = mysql.connector.connect(
        host="localhost",
        user="user",
        password="userpassword",
        database="iot_data"
    )

    if mydb.is_connected():
        mycursor = mydb.cursor()
        mycursor.execute(
            "SELECT referance.time AS referance_time, "
            "referance.data_val AS referance_value, "
            "referance.device_id AS referance_device, "
            "device.time AS device_time, "
            "device.data_val AS device_value, "
            "device.device_id AS device "
            "FROM sensor_data_cali AS referance "
            "INNER JOIN sensor_data_cali AS device "
            "ON (referance.time=SUBTIME(device.time,1) "
            "OR referance.time=device.time) "
            "AND referance.device_id='24sea0521' "
            "AND device.device_id='24sea0522';"
        )

        myresult = mycursor.fetchall()

        xpoints = np.array([row[1] for row in myresult], dtype=float)
        ypoints = np.array([row[4] for row in myresult], dtype=float)

        # ---- Raw dataset (line plot) ----
        plt.plot(xpoints, ypoints, label="Raw data")

        # ---- Polynomial best-fit (degree 2) ----
        degree = 2
        coeffs = np.polyfit(xpoints, ypoints, degree)  # e.g. [a2, a1, a0]
        # Inverse helper: compute temperature T from ADC using fitted polynomial
        def adc_to_temp(adc, coeffs, x_ref=None):
            """Return an estimated temperature corresponding to an ADC value.

            coeffs should be in highest-degree-first order as returned by
            `np.polyfit` (e.g. [a2, a1, a0] for a quadratic).
            If `x_ref` (array of reference temperatures) is provided, the
            real root closest to the mean of `x_ref` is returned.
            """
            coeffs = np.asarray(coeffs, dtype=float)
            deg = len(coeffs) - 1
            if deg == 2:
                a, b, c = coeffs
                # Solve a*T^2 + b*T + c = adc  => a*T^2 + b*T + (c - adc) = 0
                c_shift = c - float(adc)
                disc = b * b - 4 * a * c_shift
                if disc < 0:
                    return float('nan')
                sqrt_disc = np.sqrt(disc)
                t1 = (-b + sqrt_disc) / (2 * a)
                t2 = (-b - sqrt_disc) / (2 * a)
                if x_ref is not None and len(x_ref) > 0:
                    mean_ref = np.mean(x_ref)
                    return t1 if abs(t1 - mean_ref) < abs(t2 - mean_ref) else t2
                return t1 if abs(t1) < abs(t2) else t2
            elif deg == 1:
                m, c = coeffs
                if m == 0:
                    return float('nan')
                return (float(adc) - c) / m
            else:
                poly = coeffs.copy()
                poly[-1] = poly[-1] - float(adc)
                roots = np.roots(poly)
                real_roots = roots[np.isreal(roots)].real
                if real_roots.size == 0:
                    return float('nan')
                if x_ref is not None and len(x_ref) > 0:
                    mean_ref = np.mean(x_ref)
                    return real_roots[np.argmin(np.abs(real_roots - mean_ref))]
                return real_roots[0]

        y_fit = np.polyval(coeffs, xpoints)

        # Example: convert a sample ADC back to temperature
        adc_sample = float(ypoints[0]) if ypoints.size > 0 else 0.0
        temp_est = adc_to_temp(adc_sample, coeffs, x_ref=xpoints)
        print(f"Example inverse: ADC={adc_sample} -> T={temp_est:.3f}")
        plt.plot(xpoints, y_fit, label=f"Best fit (degree {degree})", color='red')

        # ---- Add formula text on plot ----
        formula_text = f"ADC = {coeffs[0]:.4f}·T² + {coeffs[1]:.4f}·T + {coeffs[2]:.4f}"
        plt.text(0.05, 0.95, formula_text, transform=plt.gca().transAxes,
                 fontsize=10, color='red', verticalalignment='top')

        # ---- Calculate and print R² ----
        y_pred = np.polyval(coeffs, xpoints)
        ss_res = np.sum((ypoints - y_pred) ** 2)
        ss_tot = np.sum((ypoints - np.mean(ypoints)) ** 2)
        r_squared = 1 - (ss_res / ss_tot)
        print(f"R² = {r_squared:.4f}")

        plt.xlabel("Reference Temperature")
        plt.ylabel("ADC Value")
        plt.title("Raw Dataset and Best-Fitted Polynomial Curve")
        plt.legend()
        plt.grid(True)
        plt.show()

        # ---- Residual plot ----
        plt.figure(figsize=(8, 4))
        plt.plot(xpoints, ypoints - y_pred, label='Residuals (y - y_fit)', color='purple')
        plt.axhline(0, color='black', linewidth=0.8, linestyle='--')
        plt.xlabel("Reference Temperature")
        plt.ylabel("Residual ADC Value")
        plt.title("Residual Plot")
        plt.legend()
        plt.grid(True)
        plt.show()

except Error as e:
    print("Error while connecting to MySQL", e)

finally:
    if mydb.is_connected():
        mycursor.close()
        mydb.close()