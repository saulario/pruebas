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
    @NamedQuery(name = "Tea.findAll", query = "SELECT t FROM Tea t"),
    @NamedQuery(name = "Tea.findByTeacod", query = "SELECT t FROM Tea t WHERE t.teacod = :teacod"),
    @NamedQuery(name = "Tea.findByTeades", query = "SELECT t FROM Tea t WHERE t.teades = :teades")})
public class Tea implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private String teacod;
    @Basic(optional = false)
    private String teades;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tc0teacod")
    private Collection<Tc0> tc0Collection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tt0teacod")
    private Collection<Tt0> tt0Collection;

    public Tea() {
    }

    public Tea(String teacod) {
        this.teacod = teacod;
    }

    public Tea(String teacod, String teades) {
        this.teacod = teacod;
        this.teades = teades;
    }

    public String getTeacod() {
        return teacod;
    }

    public void setTeacod(String teacod) {
        this.teacod = teacod;
    }

    public String getTeades() {
        return teades;
    }

    public void setTeades(String teades) {
        this.teades = teades;
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
        hash += (teacod != null ? teacod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tea)) {
            return false;
        }
        Tea other = (Tea) object;
        if ((this.teacod == null && other.teacod != null) || (this.teacod != null && !this.teacod.equals(other.teacod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tea[ teacod=" + teacod + " ]";
    }
    
}
