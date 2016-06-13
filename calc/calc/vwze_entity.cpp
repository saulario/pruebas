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
}

Zon::~Zon() {
}

bool Zon::operator==(const Zon & other) {
    if (this->zoncod != other.zoncod) return false;
    if (this->zondes != other.zondes) return false;
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
