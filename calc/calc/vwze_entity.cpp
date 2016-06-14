#include "vwze_entity.h"
using namespace vwze::entity;

Doc::Doc() {
    doccod = 0L;
    docrel = "";
    docexp = "";
    docfec = tntdb::Date();
    docorgzon = "";
    docorgpob = "";
    docdeszon = "";
    docdespob = "";
    docflu = "";
    docfab = "";
    docdun = "";
    docpro = "";
    docpes = 0.0;
    docvol = 0.0;
    docpef = 0.0;
}

Doc::~Doc() {
}

bool Doc::operator==(const Doc & other) {
    if (this->doccod != other.doccod) return false;
    if (this->docrel != other.docrel) return false;
    if (this->docexp != other.docexp) return false;
    if (this->docfec != other.docfec) return false;
    if (this->docorgzon != other.docorgzon) return false;
    if (this->docorgpob != other.docorgpob) return false;
    if (this->docdeszon != other.docdeszon) return false;
    if (this->docdespob != other.docdespob) return false;
    if (this->docflu != other.docflu) return false;
    if (this->docfab != other.docfab) return false;
    if (this->docdun != other.docdun) return false;
    if (this->docpro != other.docpro) return false;
    if (this->docpes != other.docpes) return false;
    if (this->docvol != other.docvol) return false;
    if (this->docpef != other.docpef) return false;
    return true;
}

Dod::Dod() {
    dodcod = 0L;
    dodrel = "";
    dodexp = "";
    dodfec = tntdb::Date();
    dodorgzon = "";
    dodorgpob = "";
    doddeszon = "";
    doddespob = "";
    dodflu = "";
    dodfab = "";
    doddun = "";
    dodpro = "";
    dodpes = 0.0;
    dodvol = 0.0;
    dodpef = 0.0;
}

Dod::~Dod() {
}

bool Dod::operator==(const Dod & other) {
    if (this->dodcod != other.dodcod) return false;
    if (this->dodrel != other.dodrel) return false;
    if (this->dodexp != other.dodexp) return false;
    if (this->dodfec != other.dodfec) return false;
    if (this->dodorgzon != other.dodorgzon) return false;
    if (this->dodorgpob != other.dodorgpob) return false;
    if (this->doddeszon != other.doddeszon) return false;
    if (this->doddespob != other.doddespob) return false;
    if (this->dodflu != other.dodflu) return false;
    if (this->dodfab != other.dodfab) return false;
    if (this->doddun != other.doddun) return false;
    if (this->dodpro != other.dodpro) return false;
    if (this->dodpes != other.dodpes) return false;
    if (this->dodvol != other.dodvol) return false;
    if (this->dodpef != other.dodpef) return false;
    return true;
}

Pro::Pro() {
    produn = "";
    proraz = "";
}

Pro::~Pro() {
}

bool Pro::operator==(const Pro & other) {
    if (this->produn != other.produn) return false;
    if (this->proraz != other.proraz) return false;
    return true;
}

Zon::Zon() {
    zoncod = "";
    zondes = "";
    zonman = 0.0;
}

Zon::~Zon() {
}

bool Zon::operator==(const Zon & other) {
    if (this->zoncod != other.zoncod) return false;
    if (this->zondes != other.zondes) return false;
    if (this->zonman != other.zonman) return false;
    return true;
}

Zoo::Zoo() {
    zoocod = 0L;
    zoozoncod = "";
    zoopcp = "";
}

Zoo::~Zoo() {
}

bool Zoo::operator==(const Zoo & other) {
    if (this->zoocod != other.zoocod) return false;
    if (this->zoozoncod != other.zoozoncod) return false;
    if (this->zoopcp != other.zoopcp) return false;
    return true;
}
