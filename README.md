# notePad
A simple text-editor developed with Qt creator for editing rich text files. Compiled and Tested on Ubuntu Ubuntu 20.04. with Qt 5
 

# Features
1. Multi-Tab support
2. Bold/Unbold -> Ctrl+B
3. Subscript -> Ctrl+=
4. Superscript -> Ctrl+Shift+=
3. Keyboard Shortcuts


# Installation
1. Install qt5:
- $ sudo apt-get install qt5-default

2. Make sure current directory is "notePad", compile notePad.pro and make:
- $ cd notePad
- $ qmake notepad.pro
- $ make
- Ignore the warnings.


# How to run the code?
Execute file notePad in folder "notePad"
- $ ./notePad

# Issues/Future-Work
1. Warning dialog-box will not be displayed to save the work before closing the tab.
2. Hint is not given for whether file content is changed or not.
3. Search and replace functions are not provided.
