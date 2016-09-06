package org.fl.commons;

import javax.interceptor.AroundInvoke;
import javax.interceptor.Interceptor;
import javax.interceptor.InvocationContext;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

@Loggable
@Interceptor
public class LoggerInterceptor {

    private static final Logger log = LogManager.getLogger();

    /**
     *
     * @param ic
     * @return
     */
    @AroundInvoke
    public Object doIt(final InvocationContext ic) throws Exception {
        log.info("-----> Inicio");
        Object o = null;
        
        if (true | false) {
            throw new Exception("Se ha producido un error controlado");
        }
        
        log.info("<----- Fin");
        return ic.proceed();
    }

}
