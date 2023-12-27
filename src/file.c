// This file is part of libkc_system
// ==================================
//
// file.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/file.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//


//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//


//---------------------------------------------------------------------------//

struct File* new_file()
{
  // create a file instance to be returned
  struct File* file = malloc(sizeof(struct File));

  if (file == NULL)
  {
    exit(1);
  }

  // assigns the public member methods
  file->close       = NULL;
  file->copy        = NULL;
  file->copy_path   = NULL;
  file->create_path = NULL;
  file->delete      = NULL;
  file->delete_path = NULL;
  file->get_length  = NULL;
  file->get_mode    = NULL;
  file->get_name    = NULL;
  file->is_open     = NULL;
  file->move        = NULL;
  file->move_path   = NULL;
  file->open        = NULL;
  file->read        = NULL;
  file->write       = NULL;

  return file;
}

//---------------------------------------------------------------------------//

void destroy_file(struct File* file)
{
  if (file == NULL)
  {
    exit(1);
  }

  free(file);
}

//---------------------------------------------------------------------------//

