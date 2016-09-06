package org.fl.commons;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class InterceptedClass {
    
    private static final Logger log = LogManager.getLogger();
    
    @Loggable
    public void interceptedMethod() {
        log.info("-----> Inicio");
        
        log.info("<----- Fin");
    }
    
}
