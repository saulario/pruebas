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
@Table(name = "tta")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Tta.findAll", query = "SELECT t FROM Tta t"),
    @NamedQuery(name = "Tta.findByVersion", query = "SELECT t FROM Tta t WHERE t.version = :version"),
    @NamedQuery(name = "Tta.findByTtacod", query = "SELECT t FROM Tta t WHERE t.ttacod = :ttacod"),
    @NamedQuery(name = "Tta.findByTtaloc", query = "SELECT t FROM Tta t WHERE t.ttaloc = :ttaloc"),
    @NamedQuery(name = "Tta.findByTtacypraz", query = "SELECT t FROM Tta t WHERE t.ttacypraz = :ttacypraz"),
    @NamedQuery(name = "Tta.findByTtacypidf", query = "SELECT t FROM Tta t WHERE t.ttacypidf = :ttacypidf"),
    @NamedQuery(name = "Tta.findByTtacyptkr", query = "SELECT t FROM Tta t WHERE t.ttacyptkr = :ttacyptkr")})
public class Tta implements Serializable {

    private static final long serialVersionUID = 1L;
    @Basic(optional = false)
    @Column(name = "version")
    private long version;
    @Id
    @Basic(optional = false)
    @Column(name = "ttacod")
    private Long ttacod;
    @Basic(optional = false)
    @Column(name = "ttaloc")
    private String ttaloc;
    @Basic(optional = false)
    @Column(name = "ttacypraz")
    private String ttacypraz;
    @Basic(optional = false)
    @Column(name = "ttacypidf")
    private String ttacypidf;
    @Basic(optional = false)
    @Column(name = "ttacyptkr")
    private String ttacyptkr;
    @JoinColumn(name = "ttacypcod", referencedColumnName = "cypcod")
    @ManyToOne(optional = false)
    private Cyp ttacypcod;
    @JoinColumn(name = "ttateocod", referencedColumnName = "teocod")
    @ManyToOne(optional = false)
    private Teo ttateocod;

    public Tta() {
    }

    public Tta(Long ttacod) {
        this.ttacod = ttacod;
    }

    public Tta(Long ttacod, long version, String ttaloc, String ttacypraz, String ttacypidf, String ttacyptkr) {
        this.ttacod = ttacod;
        this.version = version;
        this.ttaloc = ttaloc;
        this.ttacypraz = ttacypraz;
        this.ttacypidf = ttacypidf;
        this.ttacyptkr = ttacyptkr;
    }

    public long getVersion() {
        return version;
    }

    public void setVersion(long version) {
        this.version = version;
    }

    public Long getTtacod() {
        return ttacod;
    }

    public void setTtacod(Long ttacod) {
        this.ttacod = ttacod;
    }

    public String getTtaloc() {
        return ttaloc;
    }

    public void setTtaloc(String ttaloc) {
        this.ttaloc = ttaloc;
    }

    public String getTtacypraz() {
        return ttacypraz;
    }

    public void setTtacypraz(String ttacypraz) {
        this.ttacypraz = ttacypraz;
    }

    public String getTtacypidf() {
        return ttacypidf;
    }

    public void setTtacypidf(String ttacypidf) {
        this.ttacypidf = ttacypidf;
    }

    public String getTtacyptkr() {
        return ttacyptkr;
    }

    public void setTtacyptkr(String ttacyptkr) {
        this.ttacyptkr = ttacyptkr;
    }

    public Cyp getTtacypcod() {
        return ttacypcod;
    }

    public void setTtacypcod(Cyp ttacypcod) {
        this.ttacypcod = ttacypcod;
    }

    public Teo getTtateocod() {
        return ttateocod;
    }

    public void setTtateocod(Teo ttateocod) {
        this.ttateocod = ttateocod;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (ttacod != null ? ttacod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Tta)) {
            return false;
        }
        Tta other = (Tta) object;
        if ((this.ttacod == null && other.ttacod != null) || (this.ttacod != null && !this.ttacod.equals(other.ttacod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Tta[ ttacod=" + ttacod + " ]";
    }
    
}
