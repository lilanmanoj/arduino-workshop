## Arduino Testing Workspace
This is kind of playground for tinkering with Arduino board.
And has defined all the information and help instructions needed when create, compile and upload sketches.

Below I have added useful informations and instructions, if you using the `arduino-cli` as the development companion of your chice, just as mine.

### Sketch
Sketch is the workspace or the project according to the terms of Arduino.
It usually contains `.ino` extension file with the same name as the project directory.
Which includes C++ standard code.

to create sketch we can use the command (from arduino-cli)
```bash
arduino-cli sketch new MyArduinoSketch
```

### Inspect board and core informations
In order to view the connected arduino board following cli command can be used
```bash
arduino-cli board list
```
From above we can get the FQBN (Full Qualified Board Name) and connected port informations.
Usually they are required when compiling and uploading the sketch to the board.

To view the installed cores we can use
```bash
arduino-cli core list
```

### Complile sketch
To compile the sketch we will need to know
1. FQBN - Full Qualified Board Name which can be acquired by listing the connected boards
2. Sketch/Path - We can use `./` if the ino file is in the current directory you are in or absolute path to the sketch directory

Then we can use below command to compile the sketch
```bash
arduino-cli compile -b FQBN Sketch/Path
```

### Upload sketch
Once after successful compilation of the sketch, we can upload it to the board.
Here also we will need to know following informations prior to upload.
1. FQBN
2. PORT
3. Sketch/Path
They can be acquired by listing the connected boards, according to the step declared above.

Then we can use following command to upload the sketch
```bash
arduino-cli upload -p PORT -b FQBN Sketch/Path
```