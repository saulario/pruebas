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
    @NamedQuery(name = "Cyp.findAll", query = "SELECT c FROM Cyp c"),
    @NamedQuery(name = "Cyp.findByCypcod", query = "SELECT c FROM Cyp c WHERE c.cypcod = :cypcod"),
    @NamedQuery(name = "Cyp.findByCypraz", query = "SELECT c FROM Cyp c WHERE c.cypraz = :cypraz"),
    @NamedQuery(name = "Cyp.findByCypidf", query = "SELECT c FROM Cyp c WHERE c.cypidf = :cypidf"),
    @NamedQuery(name = "Cyp.findByCyptkr", query = "SELECT c FROM Cyp c WHERE c.cyptkr = :cyptkr")})
public class Cyp implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private Long cypcod;
    @Basic(optional = false)
    private String cypraz;
    @Basic(optional = false)
    private String cypidf;
    @Basic(optional = false)
    private String cyptkr;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tc0cypcod")
    private Collection<Tc0> tc0Collection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tt0cypcod")
    private Collection<Tt0> tt0Collection;

    public Cyp() {
    }

    public Cyp(Long cypcod) {
        this.cypcod = cypcod;
    }

    public Cyp(Long cypcod, String cypraz, String cypidf, String cyptkr) {
        this.cypcod = cypcod;
        this.cypraz = cypraz;
        this.cypidf = cypidf;
        this.cyptkr = cyptkr;
    }

    public Long getCypcod() {
        return cypcod;
    }

    public void setCypcod(Long cypcod) {
        this.cypcod = cypcod;
    }

    public String getCypraz() {
        return cypraz;
    }

    public void setCypraz(String cypraz) {
        this.cypraz = cypraz;
    }

    public String getCypidf() {
        return cypidf;
    }

    public void setCypidf(String cypidf) {
        this.cypidf = cypidf;
    }

    public String getCyptkr() {
        return cyptkr;
    }

    public void setCyptkr(String cyptkr) {
        this.cyptkr = cyptkr;
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
        hash += (cypcod != null ? cypcod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Cyp)) {
            return false;
        }
        Cyp other = (Cyp) object;
        if ((this.cypcod == null && other.cypcod != null) || (this.cypcod != null && !this.cypcod.equals(other.cypcod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Cyp[ cypcod=" + cypcod + " ]";
    }
    
}
