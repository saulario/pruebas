/* 
 * File:   Worker1.cpp
 * Author: saulario
 * 
 * Created on 15 de septiembre de 2016, 6:40
 */

#include "Worker1.h"
#include "Csoft.h"

#define __CLASS__ typeid(*this).name()

using namespace csoft::mod1;

Worker1::Worker1(const csoft::Csoft * csoft) {
}

Worker1::Worker1(const Worker1& orig) {
}

Worker1::~Worker1() {
}

void Worker1::doIt(void) {
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "---> Begin";

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "<--- End";
}

