#include "vwze_entity.h"
using namespace vwze::entity;

Doc::Doc() {
    doccod = 0L;
    docrel = "";
    docexp = "";
    docfec = tntdb::Date();
    docorgloc = "";
    docorgzon = "";
    docorgpcp = "";
    docorgpob = "";
    docdesloc = "";
    docdeszon = "";
    docdespcp = "";
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
    if (this->docorgloc != other.docorgloc) return false;
    if (this->docorgzon != other.docorgzon) return false;
    if (this->docorgpcp != other.docorgpcp) return false;
    if (this->docorgpob != other.docorgpob) return false;
    if (this->docdesloc != other.docdesloc) return false;
    if (this->docdeszon != other.docdeszon) return false;
    if (this->docdespcp != other.docdespcp) return false;
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
    dodorgloc = "";
    dodorgzon = "";
    dodorgpcp = "";
    dodorgpob = "";
    doddesloc = "";
    doddeszon = "";
    doddespcp = "";
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
    if (this->dodorgloc != other.dodorgloc) return false;
    if (this->dodorgzon != other.dodorgzon) return false;
    if (this->dodorgpcp != other.dodorgpcp) return false;
    if (this->dodorgpob != other.dodorgpob) return false;
    if (this->doddesloc != other.doddesloc) return false;
    if (this->doddeszon != other.doddeszon) return false;
    if (this->doddespcp != other.doddespcp) return false;
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
    doeorgloc = "";
    doeorgzon = "";
    doeorgpcp = "";
    doeorgpob = "";
    doedesloc = "";
    doedeszon = "";
    doedespcp = "";
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
    if (this->doeorgloc != other.doeorgloc) return false;
    if (this->doeorgzon != other.doeorgzon) return false;
    if (this->doeorgpcp != other.doeorgpcp) return false;
    if (this->doeorgpob != other.doeorgpob) return false;
    if (this->doedesloc != other.doedesloc) return false;
    if (this->doedeszon != other.doedeszon) return false;
    if (this->doedespcp != other.doedespcp) return false;
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

Elt::Elt() {
    eltcod = 0;
    eltorg = "";
    eltdes = "";
}

Elt::~Elt() {
}

bool Elt::operator==(const Elt & other) {
    if (this->eltcod != other.eltcod) return false;
    if (this->eltorg != other.eltorg) return false;
    if (this->eltdes != other.eltdes) return false;
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
    auftragsnummer = "";
    relevanz = "";
    wewa = "";
    gebiet = "";
    senderLokationsnummer = "";
    empfangerLokationsnummer = "";
    werk = "";
    transportlisteName = "";
    szenariolisteName = "";
    sumMenge = 0;
    sumKosten = 0.0;
    sumFracht = 0.0;
    hl = 0.0;
}

Kosten::~Kosten() {
}

bool Kosten::operator==(const Kosten & other) {
    if (this->auftragsnummer != other.auftragsnummer) return false;
    if (this->relevanz != other.relevanz) return false;
    if (this->wewa != other.wewa) return false;
    if (this->gebiet != other.gebiet) return false;
    if (this->senderLokationsnummer != other.senderLokationsnummer) return false;
    if (this->empfangerLokationsnummer != other.empfangerLokationsnummer) return false;
    if (this->werk != other.werk) return false;
    if (this->transportlisteName != other.transportlisteName) return false;
    if (this->szenariolisteName != other.szenariolisteName) return false;
    if (this->sumMenge != other.sumMenge) return false;
    if (this->sumKosten != other.sumKosten) return false;
    if (this->sumFracht != other.sumFracht) return false;
    if (this->hl != other.hl) return false;
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

Sendungsdate::Sendungsdate() {
    auftragsnummer = "";
    datum = tntdb::Datetime();
    relevanz = "";
    senderLokationsnummer = "";
    senderLand = "";
    senderPlz = "";
    senderOrt = "";
    empfangerLokationsnummer = "";
    empfangerLand = "";
    empfangerPlz = "";
    empfangerOrt = "";
    wewa = "";
    werk = "";
    routing = "";
    brutto = 0.0;
    volumen = 0.0;
    menge = 0;
}

Sendungsdate::~Sendungsdate() {
}

bool Sendungsdate::operator==(const Sendungsdate & other) {
    if (this->auftragsnummer != other.auftragsnummer) return false;
    if (this->datum != other.datum) return false;
    if (this->relevanz != other.relevanz) return false;
    if (this->senderLokationsnummer != other.senderLokationsnummer) return false;
    if (this->senderLand != other.senderLand) return false;
    if (this->senderPlz != other.senderPlz) return false;
    if (this->senderOrt != other.senderOrt) return false;
    if (this->empfangerLokationsnummer != other.empfangerLokationsnummer) return false;
    if (this->empfangerLand != other.empfangerLand) return false;
    if (this->empfangerPlz != other.empfangerPlz) return false;
    if (this->empfangerOrt != other.empfangerOrt) return false;
    if (this->wewa != other.wewa) return false;
    if (this->werk != other.werk) return false;
    if (this->routing != other.routing) return false;
    if (this->brutto != other.brutto) return false;
    if (this->volumen != other.volumen) return false;
    if (this->menge != other.menge) return false;
    return true;
}

Transport::Transport() {
    id = 0;
    auftragsnummer = "";
    transportId = 0;
    wewa = "";
    werk = "";
    relevanz = "";
    gebiet = "";
    transportbenne = "";
    senderLokationsnummer = "";
    empfangerLokationsnummer = "";
    sumMenge = 0;
}

Transport::~Transport() {
}

bool Transport::operator==(const Transport & other) {
    if (this->id != other.id) return false;
    if (this->auftragsnummer != other.auftragsnummer) return false;
    if (this->transportId != other.transportId) return false;
    if (this->wewa != other.wewa) return false;
    if (this->werk != other.werk) return false;
    if (this->relevanz != other.relevanz) return false;
    if (this->gebiet != other.gebiet) return false;
    if (this->transportbenne != other.transportbenne) return false;
    if (this->senderLokationsnummer != other.senderLokationsnummer) return false;
    if (this->empfangerLokationsnummer != other.empfangerLokationsnummer) return false;
    if (this->sumMenge != other.sumMenge) return false;
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
