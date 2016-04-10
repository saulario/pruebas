/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.fl.jpa;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author saulario
 */
@Entity
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Cto.findAll", query = "SELECT c FROM Cto c"),
    @NamedQuery(name = "Cto.findByCtocod", query = "SELECT c FROM Cto c WHERE c.ctocod = :ctocod"),
    @NamedQuery(name = "Cto.findByCtotkr", query = "SELECT c FROM Cto c WHERE c.ctotkr = :ctotkr"),
    @NamedQuery(name = "Cto.findByCtodes", query = "SELECT c FROM Cto c WHERE c.ctodes = :ctodes"),
    @NamedQuery(name = "Cto.findByCtoest", query = "SELECT c FROM Cto c WHERE c.ctoest = :ctoest")})
public class Cto implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private Long ctocod;
    @Basic(optional = false)
    private String ctotkr;
    @Basic(optional = false)
    private String ctodes;
    @Basic(optional = false)
    private short ctoest;

    public Cto() {
    }

    public Cto(Long ctocod) {
        this.ctocod = ctocod;
    }

    public Cto(Long ctocod, String ctotkr, String ctodes, short ctoest) {
        this.ctocod = ctocod;
        this.ctotkr = ctotkr;
        this.ctodes = ctodes;
        this.ctoest = ctoest;
    }

    public Long getCtocod() {
        return ctocod;
    }

    public void setCtocod(Long ctocod) {
        this.ctocod = ctocod;
    }

    public String getCtotkr() {
        return ctotkr;
    }

    public void setCtotkr(String ctotkr) {
        this.ctotkr = ctotkr;
    }

    public String getCtodes() {
        return ctodes;
    }

    public void setCtodes(String ctodes) {
        this.ctodes = ctodes;
    }

    public short getCtoest() {
        return ctoest;
    }

    public void setCtoest(short ctoest) {
        this.ctoest = ctoest;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (ctocod != null ? ctocod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Cto)) {
            return false;
        }
        Cto other = (Cto) object;
        if ((this.ctocod == null && other.ctocod != null) || (this.ctocod != null && !this.ctocod.equals(other.ctocod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Cto[ ctocod=" + ctocod + " ]";
    }
    
}
