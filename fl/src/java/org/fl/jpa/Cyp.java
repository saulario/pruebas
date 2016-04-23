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
@Table(name = "cyp")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Cyp.findAll", query = "SELECT c FROM Cyp c"),
    @NamedQuery(name = "Cyp.findByVersion", query = "SELECT c FROM Cyp c WHERE c.version = :version"),
    @NamedQuery(name = "Cyp.findByCypcod", query = "SELECT c FROM Cyp c WHERE c.cypcod = :cypcod"),
    @NamedQuery(name = "Cyp.findByCypraz", query = "SELECT c FROM Cyp c WHERE c.cypraz = :cypraz"),
    @NamedQuery(name = "Cyp.findByCypidf", query = "SELECT c FROM Cyp c WHERE c.cypidf = :cypidf"),
    @NamedQuery(name = "Cyp.findByCyptkr", query = "SELECT c FROM Cyp c WHERE c.cyptkr = :cyptkr")})
public class Cyp implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "cypcod")
    private Long cypcod;
    @Basic(optional = false)
    @Column(name = "cypraz")
    private String cypraz;
    @Basic(optional = false)
    @Column(name = "cypidf")
    private String cypidf;
    @Basic(optional = false)
    @Column(name = "cyptkr")
    private String cyptkr;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "ttacypcod")
    private Collection<Tta> ttaCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "tcacypcod")
    private Collection<Tca> tcaCollection;

    public Cyp() {
    }

    public Cyp(Long cypcod) {
        this.cypcod = cypcod;
    }

    public Cyp(Long cypcod, long version, String cypraz, String cypidf, String cyptkr) {
        this.cypcod = cypcod;
        this.version = version;
        this.cypraz = cypraz;
        this.cypidf = cypidf;
        this.cyptkr = cyptkr;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
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
