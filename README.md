# DialogMaster
A utility to create optimized dialogs with Qt

## Features
Provides a namespace with improved versions of all the dialogs Qt provides. By using these, things like modality, titles and window decoration get handled by the system.
The dialogs include:

- A generic method to setup any QDialog
- QMessageBox, with the common methods as well as a setup for custom message boxes
- QInputDialog
- QProgressDialog
- QFileDialog
- QColorDialog
- QFontDialog

## Installation
The package is providet as qpm package, [`de.skycoder42.dialog-master`](https://www.qpm.io/packages/de.skycoder42.dialog-master/index.html). To install:

1. Install qpm (See [GitHub - Installing](https://github.com/Cutehacks/qpm/blob/master/README.md#installing), for **windows** see below)
2. In your projects root directory, run `qpm install de.skycoder42.dialog-master`
3. Include qpm to your project by adding `include(vendor/vendor.pri)` to your `.pro` file

Check their [GitHub - Usage for App Developers](https://github.com/Cutehacks/qpm/blob/master/README.md#usage-for-app-developers) to learn more about qpm.

**Important for Windows users:** QPM Version *0.10.0* (the one you can download on the website) is currently broken on windows! It's already fixed in master, but not released yet. Until a newer versions gets released, you can download the latest dev build from here:
- https://storage.googleapis.com/www.qpm.io/download/latest/windows_amd64/qpm.exe
- https://storage.googleapis.com/www.qpm.io/download/latest/windows_386/qpm.exe
