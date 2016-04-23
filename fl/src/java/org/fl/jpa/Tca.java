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
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author saulario
 */
@Entity
@Table(name = "tca")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Tca.findAll", query = "SELECT t FROM Tca t"),
    @NamedQuery(name = "Tca.findByVersion", query = "SELECT t FROM Tca t WHERE t.version = :version"),
    @NamedQuery(name = "Tca.findByTcacod", query = "SELECT t FROM Tca t WHERE t.tcacod = :tcacod"),
    @NamedQuery(name = "Tca.findByTcaloc", query = "SELECT t FROM Tca t WHERE t.tcaloc = :tcaloc"),
    @NamedQuery(name = "Tca.findByTcacypraz", query = "SELECT t FROM Tca t WHERE t.tcacypraz = :tcacypraz"),
    @NamedQuery(name = "Tca.findByTcacypidf", query = "SELECT t FROM Tca t WHERE t.tcacypidf = :tcacypidf"),
    @NamedQuery(name = "Tca.findByTcacyptkr", query = "SELECT t FROM Tca t WHERE t.tcacyptkr = :tcacyptkr")})
public class Tca implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "tcacod")
    private Long tcacod;
    @Basic(optional = false)
    @Column(name = "tcaloc")
    private String tcaloc;
    @Basic(optional = false)
    @Column(name = "tcacypraz")
    private String tcacypraz;
    @Basic(optional = false)
    @Column(name = "tcacypidf")
    private String tcacypidf;
    @Basic(optional = false)
    @Column(name = "tcacyptkr")
    private String tcacyptkr;
    @JoinColumn(name = "tcacypcod", referencedColumnName = "cypcod")
    @ManyToOne(optional = false)
    private Cyp tcacypcod;
    @JoinColumn(name = "tcateocod", referencedColumnName = "teocod")
    @ManyToOne(optional = false)
    private Teo tcateocod;

    public Tca() {
    }

    public Tca(Long tcacod) {
        this.tcacod = tcacod;
    }

    public Tca(Long tcacod, long version, String tcaloc, String tcacypraz, String tcacypidf, String tcacyptkr) {
        this.tcacod = tcacod;
        this.version = version;
        this.tcaloc = tcaloc;
        this.tcacypraz = tcacypraz;
        this.tcacypidf = tcacypidf;
        this.tcacyptkr = tcacyptkr;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public Long getTcacod() {
        return tcacod;
    }

    public void setTcacod(Long tcacod) {
        this.tcacod = tcacod;
    }

    public String getTcaloc() {
        return tcaloc;
    }

    public void setTcaloc(String tcaloc) {
        this.tcaloc = tcaloc;
    }

    public String getTcacypraz() {
        return tcacypraz;
    }

    public void setTcacypraz(String tcacypraz) {
        this.tcacypraz = tcacypraz;
    }

    public String getTcacypidf() {
        return tcacypidf;
    }

    public void setTcacypidf(String tcacypidf) {
        this.tcacypidf = tcacypidf;
    }

    public String getTcacyptkr() {
        return tcacyptkr;
    }

    public void setTcacyptkr(String tcacyptkr) {
        this.tcacyptkr = tcacyptkr;
    }

    public Cyp getTcacypcod() {
        return tcacypcod;
    }

    public void setTcacypcod(Cyp tcacypcod) {
        this.tcacypcod = tcacypcod;
    }

    public Teo getTcateocod() {
        return tcateocod;
    }

    public void setTcateocod(Teo tcateocod) {
        this.tcateocod = tcateocod;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (tcacod != null ? tcacod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tca)) {
            return false;
        }
        Tca other = (Tca) object;
        if ((this.tcacod == null && other.tcacod != null) || (this.tcacod != null && !this.tcacod.equals(other.tcacod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tca[ tcacod=" + tcacod + " ]";
    }
    
}
