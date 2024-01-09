// This file is part of libkc_system
// ==================================
//
// file.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/testing/testing.h"
#include "../include/file.h"

#include <stdio.h>

int main()
{
  testgroup("File")
  {
    subtest("Creation and Destruction")
    {
      struct File* file = new_file();

      ok(file != NULL);
      ok(file->log != NULL);

      destroy_file(file);
    }

    subtest("Close")
    {
      struct File* file = new_file();
      ok(file->file == NULL);

      file->open(file, "test_close", KC_FILE_CREATE_ALWAYS);

      ok(file->file != NULL);
      ok(strcmp(file->mode, "w") == 0);

      file->close(file);

      ok(file->opened == false);

      destroy_file(file);
    }

    subtest("Get Path")
    {
      struct File* file = new_file();

      file->open(file, "test_close", KC_FILE_CREATE_ALWAYS);
      ok(strcmp(file->get_path(file), "test_close") == 0);

      destroy_file(file);
    }

    subtest("Is Open")
    {
      struct File* file = new_file();
      ok(file->is_open(file) == false);

      file->open(file, "test_close", KC_FILE_CREATE_ALWAYS);
      ok(file->is_open(file) == true);

      file->close(file);
      ok(file->is_open(file) == false);

      destroy_file(file);
    }

    subtest("Open")
    {
      struct File* file = new_file();
      ok(file->file == NULL);

      note("Create New")

      file->open(file, "test_open", KC_FILE_CREATE_NEW);

      ok(file->file != NULL);
      ok(strcmp(file->mode, "wx") == 0);

      note("Create Always")

      file->open(file, "test_open", KC_FILE_CREATE_ALWAYS);

      ok(file->file != NULL);
      ok(strcmp(file->mode, "w") == 0);

      note("Open Existing")

      file->open(file, "test_open", KC_FILE_OPEN_EXISTING);

      ok(file->file != NULL);
      ok(strcmp(file->mode, "r") == 0);

      note("Open Always")

      file->open(file, "test_open", KC_FILE_OPEN_ALWAYS);

      ok(file->file != NULL);
      ok(strcmp(file->mode, "a+") == 0);

      destroy_file(file);
    }

    done_testing();
  }

  return 0;
}