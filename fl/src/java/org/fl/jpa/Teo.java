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
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author saulario
 */
@Entity
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Teo.findAll", query = "SELECT t FROM Teo t"),
    @NamedQuery(name = "Teo.findByTeocod", query = "SELECT t FROM Teo t WHERE t.teocod = :teocod"),
    @NamedQuery(name = "Teo.findByTeodes", query = "SELECT t FROM Teo t WHERE t.teodes = :teodes")})
public class Teo implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private String teocod;
    @Basic(optional = false)
    private String teodes;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tc0teocod")
    private Collection<Tc0> tc0Collection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tt0teocod")
    private Collection<Tt0> tt0Collection;

    public Teo() {
    }

    public Teo(String teocod) {
        this.teocod = teocod;
    }

    public Teo(String teocod, String teodes) {
        this.teocod = teocod;
        this.teodes = teodes;
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

    @XmlTransient
    public Collection<Tc0> getTc0Collection() {
        return tc0Collection;
    }

    public void setTc0Collection(Collection<Tc0> tc0Collection) {
        this.tc0Collection = tc0Collection;
    }

    @XmlTransient
    public Collection<Tt0> getTt0Collection() {
        return tt0Collection;
    }

    public void setTt0Collection(Collection<Tt0> tt0Collection) {
        this.tt0Collection = tt0Collection;
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
