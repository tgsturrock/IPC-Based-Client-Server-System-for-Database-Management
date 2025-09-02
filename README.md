### Movie Database Application

This repository contains the source code for a C-based movie database application. The project is built on a **client-server architecture**, showcasing core concepts of **inter-process communication (IPC)** and **modular software design**. The application allows users to search for movies and update their ratings, with all database operations handled by a dedicated server program.

---

### **Overview of the Project**

The application functions as a classic client-server system. The **server** starts and listens for incoming requests. The **client**, a command-line program, handles user interaction, formats requests, and communicates with the server via **named pipes (FIFOs)**. The server processes the request by interacting with the database files and sends the results or a confirmation back to the client, which then displays them to the user.

This project demonstrates a solid foundation in software engineering, with a strong focus on modularity, documentation, and a clear separation of program components.

---

### **Repository Structure**

The project is organized with a clear separation of concerns in the directory and file structure.

* **`client/`**: This directory contains the source code for the client-side application.
    * **`client.c`**: The core source file for the client program. It handles all user interaction, serializes requests, and displays the server's responses.
    * **`src/`** and **`hdr/`**: These directories likely contain additional source code and header files for the client's modules.
* **`serveur/`**: This directory holds the source code for the server-side application.
    * **`serveur/src/`**: This subdirectory contains the main logic for the server, broken down into key modules:
        * **`imdb.c`**: Manages all database interactions, including parsing data, searching, and updating ratings.
        * **`recherche.c`**: Defines and manages the data structures for search criteria.
        * **`resultat.c`**: Manages the data structures for search results, including individual movie titles and the list of all found titles.
* **`scripts/`**: This directory contains shell scripts that automate the build and run process for both the client and server.
    * **`compile_serveur`**: A script that compiles the server's source files using `gcc`.
    * **`run_serveur`**: A script that compiles and then runs the server executable.
    * **`run_client`**: A script that compiles and runs the client executable with a sample command.
* **`applications/`**: This directory is the designated location for the compiled executables.
* **`Conception.odt`** & **`Planification_Labo3.doc`**: These documents highlight the project's development process, including the design choices and planning from the lab.

---

### **Key Features**

* **Search Engine**: Users can search the movie database using various criteria, including **title, genre, category, and release year**.
* **Movie Rating System**: A new feature allows users to **rate a movie** on a scale of 1 to 10. The server updates the database with the new score and provides the client with the newly calculated average rating.
* **Inter-Process Communication (IPC)**: The client and server programs communicate exclusively through **named pipes (FIFOs)**, demonstrating a fundamental form of IPC for exchanging data between two distinct processes.
* **Data Serialization**: The application includes custom logic to handle the serialization and deserialization of data, which is essential for reliably transmitting variable-sized data structures over the FIFOs.
