/* 
 * File:   Csoft.h
 * Author: saulario
 *
 * Created on 15 de septiembre de 2016, 6:52
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

        int doIt(int, char **);

    private:
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;
        static void launch(const Csoft *, unsigned int);
    };

}

#endif /* CSOFT_H */

