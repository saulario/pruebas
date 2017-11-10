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
    dockcc = "";
    docpes = 0;
    docvol = 0.0;
    docpef = 0;
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
    if (this->dockcc != other.dockcc) return false;
    if (this->docpes != other.docpes) return false;
    if (this->docvol != other.docvol) return false;
    if (this->docpef != other.docpef) return false;
    return true;
}

Dod::Dod() {
    dodcod = 0L;
    dodrel = "";
    dodexp = "";
    dodtip = 0;
    dodfec = tntdb::Date();
    dodorgzon = "";
    dodorgpob = "";
    doddeszon = "";
    doddespob = "";
    dodflu = "";
    dodfab = "";
    doddun = "";
    dodpro = "";
    dodpes = 0;
    dodvol = 0.0;
    dodpef = 0;
    dodkey = "";
}

Dod::~Dod() {
}

bool Dod::operator==(const Dod & other) {
    if (this->dodcod != other.dodcod) return false;
    if (this->dodrel != other.dodrel) return false;
    if (this->dodexp != other.dodexp) return false;
    if (this->dodtip != other.dodtip) return false;
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
    if (this->dodkey != other.dodkey) return false;
    return true;
}

Doe::Doe() {
    doecod = 0L;
    doerel = "";
    doetip = 0;
    doefec = tntdb::Date();
    doeorgzon = "";
    doeorgpob = "";
    doedeszon = "";
    doedespob = "";
    doeflu = "";
    doeexp = "";
    doedun = "";
    doepro = "";
    doepes = 0;
    doevol = 0.0;
    doepef = 0;
    doecnt = 0;
    doepun = 0.0;
    doetot = 0.0;
    doekey = "";
}

Doe::~Doe() {
}

bool Doe::operator==(const Doe & other) {
    if (this->doecod != other.doecod) return false;
    if (this->doerel != other.doerel) return false;
    if (this->doetip != other.doetip) return false;
    if (this->doefec != other.doefec) return false;
    if (this->doeorgzon != other.doeorgzon) return false;
    if (this->doeorgpob != other.doeorgpob) return false;
    if (this->doedeszon != other.doedeszon) return false;
    if (this->doedespob != other.doedespob) return false;
    if (this->doeflu != other.doeflu) return false;
    if (this->doeexp != other.doeexp) return false;
    if (this->doedun != other.doedun) return false;
    if (this->doepro != other.doepro) return false;
    if (this->doepes != other.doepes) return false;
    if (this->doevol != other.doevol) return false;
    if (this->doepef != other.doepef) return false;
    if (this->doecnt != other.doecnt) return false;
    if (this->doepun != other.doepun) return false;
    if (this->doetot != other.doetot) return false;
    if (this->doekey != other.doekey) return false;
    return true;
}

Flt::Flt() {
    fltcod = "";
}

Flt::~Flt() {
}

bool Flt::operator==(const Flt & other) {
    if (this->fltcod != other.fltcod) return false;
    return true;
}

Kcc::Kcc() {
    kcccod = "";
    kccnom = "";
}

Kcc::~Kcc() {
}

bool Kcc::operator==(const Kcc & other) {
    if (this->kcccod != other.kcccod) return false;
    if (this->kccnom != other.kccnom) return false;
    return true;
}

Kosten::Kosten() {
    exped = "";
    relevanz = "";
    wewa = "";
    gebiet = "";
    sender = "";
    receiver = "";
    planta = "";
    transportista = NULL;
    escenario = NULL;
    menge = 0;
    kosten = 0.0;
    fratch = 0.0;
}

Kosten::~Kosten() {
    if (transportista != NULL) {
        delete transportista;
    }
    if (escenario != NULL) {
        delete escenario;
    }
}

std::string Kosten::getTransportista(void) const {
    return (transportista != NULL ? * transportista : "");
}

void Kosten::setTransportista(const std::string & transportista_) {
    if (transportista != NULL) {
        delete transportista;
    }
    transportista = new std::string(transportista_);
}

bool Kosten::isNullTransportista(void) const {
    return (transportista == NULL);
}

void Kosten::setNullTransportista(void) {
    if (transportista != NULL) {
        delete transportista;
    }
    transportista = NULL;
}

std::string Kosten::getEscenario(void) const {
    return (escenario != NULL ? * escenario : "");
}

void Kosten::setEscenario(const std::string & escenario_) {
    if (escenario != NULL) {
        delete escenario;
    }
    escenario = new std::string(escenario_);
}

bool Kosten::isNullEscenario(void) const {
    return (escenario == NULL);
}

void Kosten::setNullEscenario(void) {
    if (escenario != NULL) {
        delete escenario;
    }
    escenario = NULL;
}

bool Kosten::operator==(const Kosten & other) {
    if (this->exped != other.exped) return false;
    if (this->relevanz != other.relevanz) return false;
    if (this->wewa != other.wewa) return false;
    if (this->gebiet != other.gebiet) return false;
    if (this->sender != other.sender) return false;
    if (this->receiver != other.receiver) return false;
    if (this->planta != other.planta) return false;
    if (this->transportista != other.transportista) return false;
    if (this->escenario != other.escenario) return false;
    if (this->menge != other.menge) return false;
    if (this->kosten != other.kosten) return false;
    if (this->fratch != other.fratch) return false;
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

Rfc::Rfc() {
    rfccod = 0L;
    rfcrul = "";
    rfcmin = 0.0;
    rfckmt = 0;
    rfczon = "";
}

Rfc::~Rfc() {
}

bool Rfc::operator==(const Rfc & other) {
    if (this->rfccod != other.rfccod) return false;
    if (this->rfcrul != other.rfcrul) return false;
    if (this->rfcmin != other.rfcmin) return false;
    if (this->rfckmt != other.rfckmt) return false;
    if (this->rfczon != other.rfczon) return false;
    return true;
}

Rfd::Rfd() {
    rfdcod = 0L;
    rfdrfccod = 0L;
    rfdmin = 0.0;
    rfdmef = 0.0;
    rfdpun = 0.0;
}

Rfd::~Rfd() {
}

bool Rfd::operator==(const Rfd & other) {
    if (this->rfdcod != other.rfdcod) return false;
    if (this->rfdrfccod != other.rfdrfccod) return false;
    if (this->rfdmin != other.rfdmin) return false;
    if (this->rfdmef != other.rfdmef) return false;
    if (this->rfdpun != other.rfdpun) return false;
    return true;
}

Todo::Todo() {
    documento = "";
    relevancia = "";
    fecha = tntdb::Datetime();
    orgpais = "";
    orgcp = "";
    orgzon = "";
    orgpob = "";
    despais = "";
    descp = "";
    deszon = "";
    despob = "";
    flujo = "";
    proveedor = "";
    planta = "";
    peso = 0;
    volumen = 0.0;
    pesofac = 0;
    ruta = "";
    kcc = "";
    nombreprov = "";
}

Todo::~Todo() {
}

bool Todo::operator==(const Todo & other) {
    if (this->documento != other.documento) return false;
    if (this->relevancia != other.relevancia) return false;
    if (this->fecha != other.fecha) return false;
    if (this->orgpais != other.orgpais) return false;
    if (this->orgcp != other.orgcp) return false;
    if (this->orgzon != other.orgzon) return false;
    if (this->orgpob != other.orgpob) return false;
    if (this->despais != other.despais) return false;
    if (this->descp != other.descp) return false;
    if (this->deszon != other.deszon) return false;
    if (this->despob != other.despob) return false;
    if (this->flujo != other.flujo) return false;
    if (this->proveedor != other.proveedor) return false;
    if (this->planta != other.planta) return false;
    if (this->peso != other.peso) return false;
    if (this->volumen != other.volumen) return false;
    if (this->pesofac != other.pesofac) return false;
    if (this->ruta != other.ruta) return false;
    if (this->kcc != other.kcc) return false;
    if (this->nombreprov != other.nombreprov) return false;
    return true;
}

Vkosten::Vkosten() {
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
    dockcc = "";
    docpes = 0;
    docvol = 0.0;
    docpef = 0;
    exped = "";
    relevanz = "";
    wewa = "";
    gebiet = "";
    sender = "";
    receiver = "";
    planta = "";
    transportista = NULL;
    escenario = NULL;
    menge = 0;
    kosten = 0.0;
    fratch = 0.0;
}

Vkosten::~Vkosten() {
    if (transportista != NULL) {
        delete transportista;
    }
    if (escenario != NULL) {
        delete escenario;
    }
}

std::string Vkosten::getTransportista(void) const {
    return (transportista != NULL ? * transportista : "");
}

void Vkosten::setTransportista(const std::string & transportista_) {
    if (transportista != NULL) {
        delete transportista;
    }
    transportista = new std::string(transportista_);
}

bool Vkosten::isNullTransportista(void) const {
    return (transportista == NULL);
}

void Vkosten::setNullTransportista(void) {
    if (transportista != NULL) {
        delete transportista;
    }
    transportista = NULL;
}

std::string Vkosten::getEscenario(void) const {
    return (escenario != NULL ? * escenario : "");
}

void Vkosten::setEscenario(const std::string & escenario_) {
    if (escenario != NULL) {
        delete escenario;
    }
    escenario = new std::string(escenario_);
}

bool Vkosten::isNullEscenario(void) const {
    return (escenario == NULL);
}

void Vkosten::setNullEscenario(void) {
    if (escenario != NULL) {
        delete escenario;
    }
    escenario = NULL;
}

bool Vkosten::operator==(const Vkosten & other) {
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
    if (this->dockcc != other.dockcc) return false;
    if (this->docpes != other.docpes) return false;
    if (this->docvol != other.docvol) return false;
    if (this->docpef != other.docpef) return false;
    if (this->exped != other.exped) return false;
    if (this->relevanz != other.relevanz) return false;
    if (this->wewa != other.wewa) return false;
    if (this->gebiet != other.gebiet) return false;
    if (this->sender != other.sender) return false;
    if (this->receiver != other.receiver) return false;
    if (this->planta != other.planta) return false;
    if (this->transportista != other.transportista) return false;
    if (this->escenario != other.escenario) return false;
    if (this->menge != other.menge) return false;
    if (this->kosten != other.kosten) return false;
    if (this->fratch != other.fratch) return false;
    return true;
}

Zon::Zon() {
    zoncod = "";
    zondes = "";
    zonman = 0.0;
    zontte = 0.0;
}

Zon::~Zon() {
}

bool Zon::operator==(const Zon & other) {
    if (this->zoncod != other.zoncod) return false;
    if (this->zondes != other.zondes) return false;
    if (this->zonman != other.zonman) return false;
    if (this->zontte != other.zontte) return false;
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
