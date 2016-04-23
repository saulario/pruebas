/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.fl.jpa;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author saulario
 */
@Entity
@Table(name = "cto")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Cto.findAll", query = "SELECT c FROM Cto c"),
    @NamedQuery(name = "Cto.findByVersion", query = "SELECT c FROM Cto c WHERE c.version = :version"),
    @NamedQuery(name = "Cto.findByCtocod", query = "SELECT c FROM Cto c WHERE c.ctocod = :ctocod"),
    @NamedQuery(name = "Cto.findByCtodes", query = "SELECT c FROM Cto c WHERE c.ctodes = :ctodes"),
    @NamedQuery(name = "Cto.findByCtoest", query = "SELECT c FROM Cto c WHERE c.ctoest = :ctoest")})
public class Cto implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "ctocod")
    private String ctocod;
    @Basic(optional = false)
    @Column(name = "ctodes")
    private String ctodes;
    @Basic(optional = false)
    @Column(name = "ctoest")
    private short ctoest;

    public Cto() {
    }

    public Cto(String ctocod) {
        this.ctocod = ctocod;
    }

    public Cto(String ctocod, long version, String ctodes, short ctoest) {
        this.ctocod = ctocod;
        this.version = version;
        this.ctodes = ctodes;
        this.ctoest = ctoest;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public String getCtocod() {
        return ctocod;
    }

    public void setCtocod(String ctocod) {
        this.ctocod = ctocod;
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
