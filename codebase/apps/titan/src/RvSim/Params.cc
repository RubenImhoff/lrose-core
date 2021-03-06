/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR                                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program RvSim
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("Program name: RvSim");
    tt->comment_text = tdrpStrDup("RvSim simulates raw IQ data with multiple trips and writes it to a netCDF file.");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[1].val = DEBUG_NORM;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_VERBOSE");
      tt->enum_def.fields[2].val = DEBUG_VERBOSE;
    tt->single_val.e = DEBUG_OFF;
    tt++;
    
    // Parameter 'instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("instance");
    tt->descr = tdrpStrDup("Process instance");
    tt->help = tdrpStrDup("Used for registration with procmap.");
    tt->val_offset = (char *) &instance - &_start_;
    tt->single_val.s = tdrpStrDup("test");
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("GATE-BY_GATE POWER,VEL,WIDTH");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'data_mode'
    // ctype is '_data_mode_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("data_mode");
    tt->descr = tdrpStrDup("How data is generated.");
    tt->help = tdrpStrDup("If SPECIFY_DATA, use trip 1 and 2 moments as specified in gate_data[] array. If RANDOM_DATA, randomly generate power, velocity and width data.");
    tt->val_offset = (char *) &data_mode - &_start_;
    tt->enum_def.name = tdrpStrDup("data_mode_t");
    tt->enum_def.nfields = 2;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("SPECIFY_DATA");
      tt->enum_def.fields[0].val = SPECIFY_DATA;
      tt->enum_def.fields[1].name = tdrpStrDup("RANDOM_DATA");
      tt->enum_def.fields[1].val = RANDOM_DATA;
    tt->single_val.e = SPECIFY_DATA;
    tt++;
    
    // Parameter 'gate_data'
    // ctype is '_gate_data_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("gate_data");
    tt->descr = tdrpStrDup("");
    tt->help = tdrpStrDup("The length of this array specifies the number of gates.");
    tt->array_offset = (char *) &_gate_data - &_start_;
    tt->array_n_offset = (char *) &gate_data_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(gate_data_t);
    tt->array_n = 1;
    tt->struct_def.name = tdrpStrDup("gate_data_t");
    tt->struct_def.nfields = 6;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("double");
      tt->struct_def.fields[0].fname = tdrpStrDup("trip1_dbm");
      tt->struct_def.fields[0].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &_gate_data->trip1_dbm - (char *) _gate_data;
      tt->struct_def.fields[1].ftype = tdrpStrDup("double");
      tt->struct_def.fields[1].fname = tdrpStrDup("trip1_vel");
      tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &_gate_data->trip1_vel - (char *) _gate_data;
      tt->struct_def.fields[2].ftype = tdrpStrDup("double");
      tt->struct_def.fields[2].fname = tdrpStrDup("trip1_width");
      tt->struct_def.fields[2].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &_gate_data->trip1_width - (char *) _gate_data;
      tt->struct_def.fields[3].ftype = tdrpStrDup("double");
      tt->struct_def.fields[3].fname = tdrpStrDup("trip2_dbm");
      tt->struct_def.fields[3].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &_gate_data->trip2_dbm - (char *) _gate_data;
      tt->struct_def.fields[4].ftype = tdrpStrDup("double");
      tt->struct_def.fields[4].fname = tdrpStrDup("trip2_vel");
      tt->struct_def.fields[4].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &_gate_data->trip2_vel - (char *) _gate_data;
      tt->struct_def.fields[5].ftype = tdrpStrDup("double");
      tt->struct_def.fields[5].fname = tdrpStrDup("trip2_width");
      tt->struct_def.fields[5].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[5].rel_offset = 
        (char *) &_gate_data->trip2_width - (char *) _gate_data;
    tt->n_struct_vals = 6;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].d = -33;
      tt->struct_vals[1].d = 10;
      tt->struct_vals[2].d = 3;
      tt->struct_vals[3].d = -50;
      tt->struct_vals[4].d = -5;
      tt->struct_vals[5].d = 4;
    tt++;
    
    // Parameter 'nsamples'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("nsamples");
    tt->descr = tdrpStrDup("Number of samples per beam.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &nsamples - &_start_;
    tt->single_val.i = 64;
    tt++;
    
    // Parameter 'nbeams'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("nbeams");
    tt->descr = tdrpStrDup("Number of beams in generated data.");
    tt->help = tdrpStrDup("Only used for RANDOM_DATA. For SPECIFY_DATA, nbeams is 1.");
    tt->val_offset = (char *) &nbeams - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'ngates'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("ngates");
    tt->descr = tdrpStrDup("Number of gates in generated data.");
    tt->help = tdrpStrDup("Only used for RANDOM_DATA. For SPECIFY_DATA, ngates is 1.");
    tt->val_offset = (char *) &ngates - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'random_dbm1_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_dbm1_low");
    tt->descr = tdrpStrDup("Low limit of trip1 power (dbm).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_dbm1_low - &_start_;
    tt->single_val.d = -90;
    tt++;
    
    // Parameter 'random_dbm1_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_dbm1_high");
    tt->descr = tdrpStrDup("High limit of trip1 power (dbm).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_dbm1_high - &_start_;
    tt->single_val.d = -30;
    tt++;
    
    // Parameter 'random_dbm_diff_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_dbm_diff_low");
    tt->descr = tdrpStrDup("Low limit of power diff (trip1 - trip2) (dbm).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_dbm_diff_low - &_start_;
    tt->single_val.d = -50;
    tt++;
    
    // Parameter 'random_dbm_diff_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_dbm_diff_high");
    tt->descr = tdrpStrDup("high limit of power diff (trip1 - trip2) (dbm).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_dbm_diff_high - &_start_;
    tt->single_val.d = 50;
    tt++;
    
    // Parameter 'random_vel1_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_vel1_low");
    tt->descr = tdrpStrDup("Low limit of trip1 velocity (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_vel1_low - &_start_;
    tt->single_val.d = -20;
    tt++;
    
    // Parameter 'random_vel1_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_vel1_high");
    tt->descr = tdrpStrDup("High limit of trip1 velocity (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_vel1_high - &_start_;
    tt->single_val.d = 20;
    tt++;
    
    // Parameter 'random_vel2_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_vel2_low");
    tt->descr = tdrpStrDup("Low limit of trip1 velocity (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_vel2_low - &_start_;
    tt->single_val.d = -20;
    tt++;
    
    // Parameter 'random_vel2_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_vel2_high");
    tt->descr = tdrpStrDup("High limit of trip1 velocity (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_vel2_high - &_start_;
    tt->single_val.d = 20;
    tt++;
    
    // Parameter 'random_width1_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_width1_low");
    tt->descr = tdrpStrDup("Low limit of trip1 width (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_width1_low - &_start_;
    tt->single_val.d = 0.5;
    tt++;
    
    // Parameter 'random_width1_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_width1_high");
    tt->descr = tdrpStrDup("High limit of trip1 width (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_width1_high - &_start_;
    tt->single_val.d = 6;
    tt++;
    
    // Parameter 'random_width2_low'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_width2_low");
    tt->descr = tdrpStrDup("Low limit of trip2 width (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_width2_low - &_start_;
    tt->single_val.d = 0.5;
    tt++;
    
    // Parameter 'random_width2_high'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("random_width2_high");
    tt->descr = tdrpStrDup("High limit of trip2 width (m/s).");
    tt->help = tdrpStrDup("RANDOM_DATA only.");
    tt->val_offset = (char *) &random_width2_high - &_start_;
    tt->single_val.d = 6;
    tt++;
    
    // Parameter 'use_exponential'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("use_exponential");
    tt->descr = tdrpStrDup("Option to simulate noise with the exponential function.");
    tt->help = tdrpStrDup("If FALSE a smooth gaussian is produced. If TRUE, the data is exponentially disctibuted about the the gaussian.");
    tt->val_offset = (char *) &use_exponential - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'exponential_lambda'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("exponential_lambda");
    tt->descr = tdrpStrDup("Mean of exponential distribution.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &exponential_lambda - &_start_;
    tt->single_val.d = 1;
    tt++;
    
    // Parameter 'force_zero_phase'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("force_zero_phase");
    tt->descr = tdrpStrDup("Option to force the phase to 0.");
    tt->help = tdrpStrDup("This has the effect of generating only real parts.");
    tt->val_offset = (char *) &force_zero_phase - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'apply_phase_codes'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("apply_phase_codes");
    tt->descr = tdrpStrDup("Apply phase codes to the IQ data.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &apply_phase_codes - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'trip1_phase_index'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("trip1_phase_index");
    tt->descr = tdrpStrDup("Index of phase shift for first pulse in file.");
    tt->help = tdrpStrDup("The pulses repeat their phases on a 32-phase cycle. In the program we compute the phase table. This is the index into that table of the first pulse in the file. This therefore applies to trip1. The transmitted phase of other pulses are determined by their position in the array of pulses in the file.");
    tt->val_offset = (char *) &trip1_phase_index - &_start_;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'negate_phase_codes'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("negate_phase_codes");
    tt->descr = tdrpStrDup("Option to multiple phase codes by -1.");
    tt->help = tdrpStrDup("In some data sets the phase codes are negated. Set this to true for such data cases.");
    tt->val_offset = (char *) &negate_phase_codes - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("RADAR AND SCAN DETAILS.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'wavelength'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("wavelength");
    tt->descr = tdrpStrDup("The wavelength of the radar (cm)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &wavelength - &_start_;
    tt->single_val.d = 10;
    tt++;
    
    // Parameter 'prt'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("prt");
    tt->descr = tdrpStrDup("The PRT of the data (miscro-secs)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &prt - &_start_;
    tt->single_val.i = 1000;
    tt++;
    
    // Parameter 'start_gate'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("start_gate");
    tt->descr = tdrpStrDup("The start gate number in the data set");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &start_gate - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'start_az'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("start_az");
    tt->descr = tdrpStrDup("The starting azimuith for the data (deg)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &start_az - &_start_;
    tt->single_val.d = 30;
    tt++;
    
    // Parameter 'delta_az'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("delta_az");
    tt->descr = tdrpStrDup("The delta azimuth between samples (deg)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &delta_az - &_start_;
    tt->single_val.d = 0.01;
    tt++;
    
    // Parameter 'elevation'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("elevation");
    tt->descr = tdrpStrDup("The elevation angle of the data (deg)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &elevation - &_start_;
    tt->single_val.d = 0.5;
    tt++;
    
    // Parameter 'receiver_noise'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("receiver_noise");
    tt->descr = tdrpStrDup("Receiver noise (watts)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &receiver_noise - &_start_;
    tt->single_val.d = 1e-06;
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("TRUTH DATA OPTIONS.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'truth_method'
    // ctype is '_truth_method_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("truth_method");
    tt->descr = tdrpStrDup("Specifies how truth data is determined.");
    tt->help = tdrpStrDup("THEORETICAL_TRUTH: the theoretical values of p, v amd w used to simulate the spectra. PP_TRUTH: the pulse-pair estimates of the moments. FFT_TRUTH - the spectral estimates of the moments.");
    tt->val_offset = (char *) &truth_method - &_start_;
    tt->enum_def.name = tdrpStrDup("truth_method_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("THEORETICAL_TRUTH");
      tt->enum_def.fields[0].val = THEORETICAL_TRUTH;
      tt->enum_def.fields[1].name = tdrpStrDup("FFT_TRUTH");
      tt->enum_def.fields[1].val = FFT_TRUTH;
      tt->enum_def.fields[2].name = tdrpStrDup("PP_TRUTH");
      tt->enum_def.fields[2].val = PP_TRUTH;
    tt->single_val.e = THEORETICAL_TRUTH;
    tt++;
    
    // Parameter 'Comment 5'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 5");
    tt->comment_hdr = tdrpStrDup("OUTPUT FILE.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_dir");
    tt->descr = tdrpStrDup("Output directory for NetCDF files.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("./output");
    tt++;
    
    // Parameter 'n_files'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("n_files");
    tt->descr = tdrpStrDup("Number of output files.");
    tt->help = tdrpStrDup("You can choose to write multiple output files. This allows you to keep the size of each file down, which saves on memory usage because the entire netCDF file must be kept in memory. See output_file_name for details on file naming.");
    tt->val_offset = (char *) &n_files - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'output_file_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_file_name");
    tt->descr = tdrpStrDup("Name of output file.");
    tt->help = tdrpStrDup("The .nc extension is added to this name. If n_files is greater than 1, the file number is added to the name between the name and the extension.");
    tt->val_offset = (char *) &output_file_name - &_start_;
    tt->single_val.s = tdrpStrDup("test");
    tt++;
    
    // Parameter 'write_ldata_info_file'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("write_ldata_info_file");
    tt->descr = tdrpStrDup("Option to write _latest_data_info file in output dir.");
    tt->help = tdrpStrDup("If TRUE, _latest_data_info is written to the output directory.");
    tt->val_offset = (char *) &write_ldata_info_file - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'write_spectra_files'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("write_spectra_files");
    tt->descr = tdrpStrDup("Option to write various gate spectra to ASCII files.");
    tt->help = tdrpStrDup("If true, spectra are written to files in directory spectra_output_dir.");
    tt->val_offset = (char *) &write_spectra_files - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'spectra_output_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("spectra_output_dir");
    tt->descr = tdrpStrDup("Spectra file directory.");
    tt->help = tdrpStrDup("See 'write_spectra_files.");
    tt->val_offset = (char *) &spectra_output_dir - &_start_;
    tt->single_val.s = tdrpStrDup("./spectra");
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
