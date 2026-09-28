# Image Steganography using C

## 📌 Project Overview

Image Steganography is a technique used to hide secret information inside an image without visibly changing the image.

This project is a **C-based command-line application** that allows users to:

* Encode secret text data into a BMP image.
* Decode and extract the hidden text from the encoded BMP image.
* Validate command-line arguments and input files.
* Check whether the selected image has enough capacity to store the secret data.

## 🚀 Features

* Secret data encoding into BMP images.
* Secret data decoding from encoded BMP images.
* Bitwise operations for data embedding and extraction.
* BMP image header handling.
* File handling for images and secret data.
* Command-line argument validation.
* Image capacity checking.
* Modular programming using separate source and header files.

## 🛠️ Technologies and Concepts

* **Language:** C
* **Image Format:** BMP
* **Concepts:** Bitwise Operations, File Handling, Pointers, Structures, Command-Line Arguments
* **Environment:** Linux / WSL
* **Compiler:** GCC
* **Version Control:** Git and GitHub

## 📂 Project Structure

```text
Image-Steganography-in-C/
│
├── main.c          # Main program and command-line handling
├── encode.c        # Encoding implementation
├── encode.h        # Encoding function declarations
├── decode.c        # Decoding implementation
├── decode.h        # Decoding function declarations
├── types.h         # Project data types
├── common.h        # Common definitions
│
├── beautiful.bmp   # Sample BMP image
├── secret.txt      # Sample secret message
├── .gitignore      # Files excluded from Git
└── README.md       # Project documentation
```

## ⚙️ Compilation

Compile the project using GCC:

```bash
gcc main.c encode.c decode.c -o stego
```

## 🔐 Enc
