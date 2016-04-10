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
    @NamedQuery(name = "Seq.findAll", query = "SELECT s FROM Seq s"),
    @NamedQuery(name = "Seq.findBySeqcod", query = "SELECT s FROM Seq s WHERE s.seqcod = :seqcod"),
    @NamedQuery(name = "Seq.findBySeqdes", query = "SELECT s FROM Seq s WHERE s.seqdes = :seqdes"),
    @NamedQuery(name = "Seq.findBySegnxt", query = "SELECT s FROM Seq s WHERE s.segnxt = :segnxt")})
public class Seq implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    private String seqcod;
    @Basic(optional = false)
    private String seqdes;
    @Basic(optional = false)
    private long segnxt;

    public Seq() {
    }

    public Seq(String seqcod) {
        this.seqcod = seqcod;
    }

    public Seq(String seqcod, String seqdes, long segnxt) {
        this.seqcod = seqcod;
        this.seqdes = seqdes;
        this.segnxt = segnxt;
    }

    public String getSeqcod() {
        return seqcod;
    }

    public void setSeqcod(String seqcod) {
        this.seqcod = seqcod;
    }

    public String getSeqdes() {
        return seqdes;
    }

    public void setSeqdes(String seqdes) {
        this.seqdes = seqdes;
    }

    public long getSegnxt() {
        return segnxt;
    }

    public void setSegnxt(long segnxt) {
        this.segnxt = segnxt;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (seqcod != null ? seqcod.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Seq)) {
            return false;
        }
        Seq other = (Seq) object;
        if ((this.seqcod == null && other.seqcod != null) || (this.seqcod != null && !this.seqcod.equals(other.seqcod))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "org.fl.jpa.Seq[ seqcod=" + seqcod + " ]";
    }
    
}
