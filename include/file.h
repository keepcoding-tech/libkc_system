// This file is part of libkc_system
// ==================================
//
// file.h
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * A structure representing file handling functionalities in libkc_system.
 *
 * The File structure encapsulates file interactions, providing methods to 
 * manipulate files, retrieve file metadata, and perform file operations within
 * the libkc_system library.
 */

#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------//

#define KC_FILE_CREATE_NEW                                           0x00000001
#define KC_FILE_CREATE_ALWAYS                                        0x00000002
#define KC_FILE_OPEN_EXISTING                                        0x00000004
#define KC_FILE_OPEN_ALWAYS                                          0x00000008

#define KC_FILE_READ                                                 0x00000010
#define KC_FILE_WRITE                                                0x00000020
#define KC_FILE_DELETE                                               0x00000040

//---------------------------------------------------------------------------//

struct File
{
  struct ConsoleLog* log;

  FILE* file;

  char* path;
  char* mode;

  bool  opened;

  void    (*close)        (struct File* self);
  int     (*copy)         (struct File* self, char* from, char* to, bool replace);
  int     (*copy_path)    (struct File* self, char* from, char* to);
  int     (*create_path)  (struct File* self, char* path);
  int     (*delete)       (struct File* self, char* name);
  int     (*delete_path)  (struct File* self, char* path, bool files);
  char*   (*get_path)     (struct File* self);
  int     (*get_mode)     (struct File* self);
  int64_t (*get_length)   (struct File* self);
  bool    (*is_open)      (struct File* self);
  int     (*move)         (struct File* self, char* from, char* to);
  int     (*move_path)    (struct File* self, char* from, char* to);
  int     (*open)         (struct File* self, char* name, unsigned int mode);
  int64_t (*read)         (struct File* self, void* buffer, unsigned int length);
  bool    (*write)        (struct File* self, void* buffer, unsigned int length);
};

// the constructor should be used to create new files
struct File* new_file();

// the destructor should be used to destroy files
void destroy_file(struct File* file);

#endif /* FILE_H */