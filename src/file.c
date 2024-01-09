// This file is part of libkc_system
// ==================================
//
// file.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#define _CRT_SECURE_NO_WARNINGS

#include "../deps/libkc/logger/logger.h"
#include "../include/file.h"

#include <stdlib.h>

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static void  close_file     (struct File* self);
static char* get_file_path  (struct File* self);
static bool  get_opened     (struct File* self);
static int   open_file      (struct File* self, char* name, unsigned int mode);

//---------------------------------------------------------------------------//

struct File* new_file()
{
  // create a file instance to be returned
  struct File* file = malloc(sizeof(struct File));

  if (file == NULL)
  {
    log_fatal(err[KC_OUT_OF_MEMORY], log_err[KC_OUT_OF_MEMORY],
      __FILE__, __LINE__, __func__);
  }

  struct ConsoleLog* log = new_console_log(err, log_err, __FILE__);

  // assigns the public member fields
  file->log    = log;
  file->file   = NULL;
  file->path   = NULL;
  file->mode   = NULL;
  file->opened = false;

  // assigns the public member methods
  file->close       = close_file;
  file->copy        = NULL;
  file->copy_path   = NULL;
  file->create_path = NULL;
  file->delete      = NULL;
  file->delete_path = NULL;
  file->get_length  = NULL;
  file->get_mode    = NULL;
  file->get_path    = get_file_path;
  file->is_open     = get_opened;
  file->move        = NULL;
  file->move_path   = NULL;
  file->open        = open_file;
  file->read        = NULL;
  file->write       = NULL;

  return file;
}

//---------------------------------------------------------------------------//

void destroy_file(struct File* file)
{
  if (file == NULL)
  {
    log_fatal(err[KC_NULL_REFERENCE], log_err[KC_NULL_REFERENCE],
      __FILE__, __LINE__, __func__);
  }

  destroy_console_log(file->log);

  // close the file if still open
  file->close(file);

  free(file);
}

//---------------------------------------------------------------------------//

void close_file(struct File* self)
{
  if (self == NULL)
  {
    log_fatal(err[KC_NULL_REFERENCE], log_err[KC_NULL_REFERENCE],
      __FILE__, __LINE__, __func__);
  }

  if (self->file != NULL && self->opened == true)
  {
    fclose(self->file);
    self->file = NULL;
    self->opened = false;
  }
}

//---------------------------------------------------------------------------//

char* get_file_path(struct File* self)
{
  if (self == NULL)
  {
    log_fatal(err[KC_NULL_REFERENCE], log_err[KC_NULL_REFERENCE],
      __FILE__, __LINE__, __func__);
  }

  return self->path;
}

//---------------------------------------------------------------------------//

bool get_opened(struct File* self)
{
  if (self == NULL)
  {
    log_fatal(err[KC_NULL_REFERENCE], log_err[KC_NULL_REFERENCE],
      __FILE__, __LINE__, __func__);
  }

  return self->opened;
}

//---------------------------------------------------------------------------//

int open_file(struct File* self, char* path, unsigned int mode)
{
  if (self == NULL)
  {
    log_fatal(err[KC_NULL_REFERENCE], log_err[KC_NULL_REFERENCE],
      __FILE__, __LINE__, __func__);
  }

   self->mode = NULL;

  // Create new file, fail if exists
  if (mode & KC_FILE_CREATE_NEW)
  {
    self->mode = "wx";
  }
  
  // Create new file, overwrite if exists
  if (mode & KC_FILE_CREATE_ALWAYS)
  {
    self->mode = "w";
  }

  // Open existing file, fail if not exists
  if (mode & KC_FILE_OPEN_EXISTING)
  {
    self->mode = "r";
  }

  // Open existing file or create new
  if (mode & KC_FILE_OPEN_ALWAYS)
  {
    self->mode = "a+";
  }

  if (self->mode == NULL)
  {
    // Invalid mode provided
    self->log->error(self->log, KC_INVALID_ARGUMENT, __LINE__, __func__);

    return -1;
  }

  self->file = fopen(path, self->mode);

  if (self->file == NULL)
  {
    // File opening failed
    self->log->error(self->log, KC_FILE_NOT_FOUND, __LINE__, __func__);
    return -1;
  }

  self->path   = path; // save the path
  self->opened = true; // file is open

  return 0; // Return success status
}

//---------------------------------------------------------------------------//

