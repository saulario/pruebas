package org.cargo.commons.bootstrap;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.cargo.interceptors.Audit;

public class ClaseAuditada {

    private static final Logger log = LogManager.getLogger(ClaseAuditada.class);

    @Audit
    public void metodoAuditado() {
        log.info("-----> Inicio");

        log.info("<----- Fin");
    }

}
