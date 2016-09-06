/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.fl.jpa;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author saulario
 */
@Entity
@Table(name = "teo")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Teo.findAll", query = "SELECT t FROM Teo t"),
    @NamedQuery(name = "Teo.findByVersion", query = "SELECT t FROM Teo t WHERE t.version = :version"),
    @NamedQuery(name = "Teo.findByTeocod", query = "SELECT t FROM Teo t WHERE t.teocod = :teocod"),
    @NamedQuery(name = "Teo.findByTeodes", query = "SELECT t FROM Teo t WHERE t.teodes = :teodes"),
    @NamedQuery(name = "Teo.findByTeodef", query = "SELECT t FROM Teo t WHERE t.teodef = :teodef")})
public class Teo implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "teocod")
    private String teocod;
    @Basic(optional = false)
    @Column(name = "teodes")
    private String teodes;
    @Basic(optional = false)
    @Column(name = "teodef")
    private short teodef;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "ttateocod")
    private Collection<Tta> ttaCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tcateocod")
    private Collection<Tca> tcaCollection;

    public Teo() {
    }

    public Teo(String teocod) {
        this.teocod = teocod;
    }

    public Teo(String teocod, long version, String teodes, short teodef) {
        this.teocod = teocod;
        this.version = version;
        this.teodes = teodes;
        this.teodef = teodef;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public String getTeocod() {
        return teocod;
    }

    public void setTeocod(String teocod) {
        this.teocod = teocod;
    }

    public String getTeodes() {
        return teodes;
    }

    public void setTeodes(String teodes) {
        this.teodes = teodes;
    }

    public short getTeodef() {
        return teodef;
    }

    public void setTeodef(short teodef) {
        this.teodef = teodef;
    }

    @XmlTransient
    public Collection<Tta> getTtaCollection() {
        return ttaCollection;
    }

    public void setTtaCollection(Collection<Tta> ttaCollection) {
        this.ttaCollection = ttaCollection;
    }

    @XmlTransient
    public Collection<Tca> getTcaCollection() {
        return tcaCollection;
    }

    public void setTcaCollection(Collection<Tca> tcaCollection) {
        this.tcaCollection = tcaCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (teocod != null ? teocod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Teo)) {
            return false;
        }
        Teo other = (Teo) object;
        if ((this.teocod == null && other.teocod != null) || (this.teocod != null && !this.teocod.equals(other.teocod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Teo[ teocod=" + teocod + " ]";
    }
    
}
