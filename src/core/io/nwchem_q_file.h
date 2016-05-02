/*
 *
 *                This source code is part of
 *                    ******************
 *                    ***   Pteros   ***
 *                    ******************
 *                 molecular modeling library
 *
 * Copyright (c) 2009-2013, Semen Yesylevskyy
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of Artistic License:
 *
 * Please note, that Artistic License is slightly more restrictive
 * then GPL license in terms of distributing the modified versions
 * of this software (they should be approved first).
 * Read http://www.opensource.org/licenses/artistic-license-2.0.php
 * for details. Such license fits scientific software better then
 * GPL because it prevents the distribution of bugged derivatives.
 *
*/

#ifndef NWCHEM_Q_FILE_H
#define NWCHEM_Q_FILE_H

#include <string>
#include <fstream>
#include "pteros/core/mol_file.h"

namespace pteros {

/// Reader for GRO files. It doesn't use VMD plugins because it doesn't support writing
class Q_file: public Mol_file {
public:
    // High-level API        
    Q_file(std::string& fname): Mol_file(fname) {}
    virtual void open(char open_mode);
    virtual ~Q_file();

    virtual Mol_file_content get_content_type() const {
        return MFC_ATOMS | MFC_COORD;
    }

protected:

    std::fstream f;

    virtual bool do_read(System *sys, Frame *frame, const Mol_file_content& what);
    virtual void do_write(const Selection &sel, const Mol_file_content& what);
};

}
#endif /* MOL_FILE_H */
