package org.fl.commons;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 *
 * @author saulario
 */
public class StartupServlet extends HttpServlet {
    
    public static final Logger log = LogManager.getLogger();

    /**
     * 
     * @throws ServletException 
     */
    @Override
    public void init() throws ServletException {
        log.info("-----> Inicio");
        
                
        log.info("<----- Fin");
    }

}
