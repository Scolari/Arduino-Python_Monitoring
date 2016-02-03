
//import java.util.TimerTask;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import static java.util.concurrent.TimeUnit.SECONDS;


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author ascolari
 */
public class timertest {
    public static void main(String args[]) {
        ScheduledExecutorService exec = Executors.newSingleThreadScheduledExecutor();
        exec.scheduleAtFixedRate(new Runnable() {
            @Override
            public void run() {
                System.out.println("printing");
            }
        }, 0, 5, TimeUnit.SECONDS);
    }
}

/*
class BeeperControl {
   private final ScheduledExecutorService scheduler1 = Executors.newScheduledThreadPool(1);

   public void neep() {
     
       final Runnable beeper = new Runnable() {
       public void run() { System.out.println("beep"); }
     };
     
     scheduler1.scheduleAtFixedRate(beeper, 10, 10, SECONDS);
     
     scheduler.schedule(new Runnable() {
       public void run() { 
           beeperHandle.cancel(true); 
       }
     }, 60 * 60, SECONDS);
   }
 }*/