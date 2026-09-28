# Inverted Search in C

## Overview

Inverted Search is a command-line search application developed in **C** that indexes words from multiple text files and allows users to search the indexed database efficiently.

The project implements an inverted indexing mechanism using **hash tables and linked lists** to maintain relationships between words and the files in which they occur.

## Key Features

* Create an inverted index from multiple text files.
* Search for words in the indexed database.
* Display the indexed database.
* Update the index.
* Save the database.
* Validate input files.
* Handle dynamic memory allocation.
* Work with multiple text files.

## How It Works

During indexing, words from the input text files are processed and stored in a hash-table-based structure.

Each indexed word maintains information about the files in which that word occurs. Linked lists are used to manage multiple entries associated with the same word or file.

When a user performs a search, the application uses the indexed structure to locate the required word and identify its associated files.

## Implementation

The project uses:

* Hash tables for indexing
* Linked lists for maintaining file information
* Pointers for dynamic data management
* File handling for reading and storing data
* Structures for organizing index information

The application also supports database operations such as create, search, display, update, and save.

## Technologies

* C
* Data Structures
* Hash Tables
* Linked Lists
* File Handling
* Dynamic Memory
* Pointers

## Objective

The project demonstrates practical implementation of indexing and searching techniques while strengthening understanding of data structures, hashing, linked lists, pointers, dynamic memory allocation, and file handling in C.
