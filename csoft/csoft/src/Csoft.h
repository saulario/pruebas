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
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <thread>

#ifndef CSOFT_H
#define CSOFT_H

namespace csoft {

    class Csoft {
    public:
        Csoft();
        Csoft(const Csoft& orig);
        virtual ~Csoft();

        int doIt(int argc, char **argv);

    private:
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;
        static void launch(const Csoft *, const unsigned int);
    };

}

#endif /* CSOFT_H */

