////////////////////////////////////////////////////////////////////////////////
/// Copyright 2025 Daniel S. Buckstein
/// 
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
/// http ://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
////////////////////////////////////////////////////////////////////////////////

/*
* cat_thread.c
* Thread management implementation.
*/


#include "cat/utility/cat_thread.h"
#include "cat/cat_platform.inl"

#include <threads.h>


cat_implementation_begin;


typedef struct cat_thrd_param_s
{
    cat_thread_func_t thread_func;
    void* const* argv;
    size_t argc;
} cat_thrd_param_t;

static int cat_thrd_internal_entry_point(cat_thrd_param_t const* const p_params)
{
    assert_or_bail(p_params) 0;
    assert_or_bail(p_params->thread_func) 0;
    assert_or_bail((p_params->argc == 0) || p_params->argv) 0;
    return p_params->thread_func((int)p_params->argc, p_params->argv);
}


cat_impl int cat_thrd_create(thrd_t* const p_thread_out, cat_thread_func_t const thread_func, uint8_t const argc, void* const argv[])
{
    cat_thrd_param_t params = { 0 };
    assert_or_bail(p_thread_out) thrd_error;
    assert_or_bail(thread_func) thrd_error;
    assert_or_bail((argc == 0) || argv) thrd_error;
    params.thread_func = thread_func;
    params.argv = argv;
    params.argc = argc;
    return thrd_create(p_thread_out, cat_thrd_internal_entry_point, &params);
}

cat_impl bool cat_thread_rename(cstr_t const name)
{
    assert_or_bail(name) false;

    return false;
}


cat_implementation_end;