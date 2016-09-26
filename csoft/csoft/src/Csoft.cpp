/*
 * csoft (csoft)
 * Copyright (C) 2016..  Saul Correas Subias 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <thread>

#include "Csoft.h"
#include "mod1/Worker1.h"
#include "mod2/Worker2.h"

using namespace csoft;

Csoft::Csoft() {
}

Csoft::Csoft(const Csoft& orig) {
}

Csoft::~Csoft() {
}

int Csoft::doIt(int argc, char **argv) {
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "---> " << __PRETTY_FUNCTION__;

    std::thread t1(Csoft::launch, this, 1);
    std::thread t2(Csoft::launch, this, 2);

    t1.join();
    t2.join();

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "<--- " << __PRETTY_FUNCTION__;
    return EXIT_SUCCESS;
}

void Csoft::launch(const Csoft * csoft, const unsigned int i) {
    switch (i) {
        case 1:
        {
            mod1::Worker1 w1(csoft);
            w1.doIt();
        }
            break;
        case 2:
        {
            mod2::Worker2 w2(csoft);
            w2.doIt();
        }
            break;
    }
}