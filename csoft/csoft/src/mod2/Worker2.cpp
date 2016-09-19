/* 
 * File:   Worker2.cpp
 * Author: saulario
 * 
 * Created on 15 de septiembre de 2016, 6:40
 */

#include "Worker2.h"
#include "Csoft.h"

using namespace csoft::mod2;

Worker2::Worker2(const csoft::Csoft * csoft) {
}

Worker2::Worker2(const Worker2& orig) {
}

Worker2::~Worker2() {
}

void Worker2::doIt(void) {
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "---> Begin";

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "<--- End";    
}