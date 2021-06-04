/*
 * This file is a part of
 *
 * ============================================
 * ###   Pteros molecular modeling library  ###
 * ============================================
 *
 * https://github.com/yesint/pteros
 *
 * (C) 2009-2021, Semen Yesylevskyy
 *
 * All works, which use Pteros, should cite the following papers:
 *
 *  1.  Semen O. Yesylevskyy, "Pteros 2.0: Evolution of the fast parallel
 *      molecular analysis library for C++ and python",
 *      Journal of Computational Chemistry, 2015, 36(19), 1480–1488.
 *      doi: 10.1002/jcc.23943.
 *
 *  2.  Semen O. Yesylevskyy, "Pteros: Fast and easy to use open-source C++
 *      library for molecular analysis",
 *      Journal of Computational Chemistry, 2012, 33(19), 1632–1636.
 *      doi: 10.1002/jcc.22989.
 *
 * This is free software distributed under Artistic License:
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 *
*/


#pragma once

#include <string>
#include <functional>
#include "pteros/analysis/options.h"
#include "pteros/analysis/task_base.h"


namespace pteros {

using Task_ptr = std::shared_ptr<TaskBase> ;
using DataChannel = MessageChannel<std::shared_ptr<pteros::DataContainer> > ;
using DataChannel_ptr = std::shared_ptr<DataChannel> ;

/** The base class for trajectory processing
*   It provides facilities for loading large trajectories by frames
*   and to analyze each frame by user-defined function.
*   The range of processing could be given
*   by frame number or by physical time.
*/
class TrajectoryReader {
public:

        /// Default constructor
        TrajectoryReader();
        /// Constructor with options
        TrajectoryReader(const Options& opt);
        /// Destructor
        virtual ~TrajectoryReader(){}

        /// Pass options
        void set_options(const Options& opt);

        /// Read trajectory
        virtual void run();

        /// Print summary of allowed options
        std::string help();

        /// Adds new task
        void add_task(TaskBase* task);
        void add_task(const Task_ptr& task);

private:
        // Options
        Options options;

        std::vector<std::string> traj_files;
        std::vector<Task_ptr> tasks;

        bool is_parallel;
};

}






