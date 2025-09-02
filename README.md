###  Movie Database Application: Client-Server Architecture

This project is a C-based application that manages a movie database. Developed as part of a software engineering lab, it demonstrates key concepts in **inter-process communication (IPC)** by using a **client-server model**. The server program handles all database operations, while the client program manages user interaction. This architecture allows the two components to run independently and communicate to execute search and rating requests.

---

### **Key Features**

* **Search Engine**: Users can search the movie database using various criteria, including **title, genre, category, and release year**. The server processes the request and returns all matching entries.
* **Movie Rating System**: A new feature allows users to **rate a movie** from the search results on a scale of 1 to 10. The server updates the database with the new score and provides the client with the newly calculated average rating.
* **Inter-Process Communication (IPC)**: The client and server programs communicate exclusively through **named pipes (FIFOs)**. This method was chosen to demonstrate a fundamental form of IPC for exchanging data between two distinct programs.
* **Data Serialization**: Custom logic was implemented to handle the serialization and deserialization of data, allowing for the reliable transmission of variable-sized data structures (like search results) over the FIFOs.

---

### **Project Structure**

The codebase is organized into a modular design, with each file responsible for a specific set of functionalities. This structure promotes readability and maintainability.

* **`serveur.c`**: This is the main server program. It's responsible for creating the named pipes, listening for client connections, and managing the entire request-response lifecycle. It reads the client's request, calls the appropriate functions to handle it, and sends the results back.
* **`recherche.c`**: This module defines and manages the **search criteria**. It encapsulates the `t_critere` structure and provides functions to create, modify, and access the search parameters.
* **`resultat.c`**: This module is a container for the search results. It defines the `t_titre` structure for a single movie entry and the `t_resultat` structure, which holds the list of all movies found. It also includes functions for adding new results and calculating average ratings.
* **`imdb.c`**: This module acts as the interface to the database files. It contains the logic for **parsing the TSV files**, comparing entries against search criteria, and managing the updates to the movie ratings.
