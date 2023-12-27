// This file is part of libkc_system
// ==================================
//
// file.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 *
 */

#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------//

#define KC_FILE_CREATE_NEW                                            0x00000001
#define KC_FILE_CREATE_ALWAYS                                         0x00000002
#define KC_FILE_OPEN_EXISTING                                         0x00000004
#define KC_FILE_OPEN_ALWAYS                                           0x00000008

#define KC_FILE_READ                                                  0x00000010
#define KC_FILE_WRITE                                                 0x00000020
#define KC_FILE_DELETE                                                0x00000040

//---------------------------------------------------------------------------//

#define MAX_PATH 256

struct File
{
  // the file path
  char path[MAX_PATH];

  // the file name
  char file[MAX_PATH];

  void    (*close)        ();
  int     (*copy)         (char* from, char* to, bool replace);
  int     (*copy_path)    (char* from, char* to);
  int     (*create_path)  (char* path);
  int     (*delete)       (char* name);
  int     (*delete_path)  (char* path, bool files);
  char*   (*get_name)     ();
  int     (*get_mode)     ();
  int64_t (*get_length)   ();
  bool    (*is_open)      ();
  int     (*move)         (char* from, char* to);
  int     (*move_path)    (char* from, char* to);
  int     (*open)         (char* name, int64_t mode);
  int64_t (*read)         (void* buffer, int64_t length);
  bool    (*write)        (void* buffer, int64_t length);
};

// the constructor should be used to create new files
struct File* new_file();

// the destructor should be used to destroy files
void destroy_file(struct File* file);

#endif /* FILE_H */