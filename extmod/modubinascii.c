/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Paul Sokolovsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "py/nlr.h"
#include "py/runtime.h"
#include "py/binary.h"

#if MICROPY_PY_UBINASCII

STATIC mp_obj_t mod_binascii_hexlify(mp_uint_t n_args, const mp_obj_t *args) {
    (void)n_args;
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);

    vstr_t vstr;
    vstr_init_len(&vstr, bufinfo.len * 2);
    byte *in = bufinfo.buf, *out = (byte*)vstr.buf;
    for (mp_uint_t i = bufinfo.len; i--;) {
        byte d = (*in >> 4);
        if (d > 9) {
            d += 'a' - '9' - 1;
        }
        *out++ = d + '0';
        d = (*in++ & 0xf);
        if (d > 9) {
            d += 'a' - '9' - 1;
        }
        *out++ = d + '0';
    }
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mod_binascii_hexlify_obj, 1, 2, mod_binascii_hexlify);

STATIC const mp_map_elem_t mp_module_binascii_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_ubinascii) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_hexlify), (mp_obj_t)&mod_binascii_hexlify_obj },
//    { MP_OBJ_NEW_QSTR(MP_QSTR_unhexlify), (mp_obj_t)&mod_binascii_unhexlify_obj },
//    { MP_OBJ_NEW_QSTR(MP_QSTR_a2b_base64), (mp_obj_t)&mod_binascii_a2b_base64_obj },
//    { MP_OBJ_NEW_QSTR(MP_QSTR_b2a_base64), (mp_obj_t)&mod_binascii_b2a_base64_obj },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_binascii_globals, mp_module_binascii_globals_table);

const mp_obj_module_t mp_module_ubinascii = {
    .base = { &mp_type_module },
    .name = MP_QSTR_ubinascii,
    .globals = (mp_obj_dict_t*)&mp_module_binascii_globals,
};

#endif //MICROPY_PY_UBINASCII
