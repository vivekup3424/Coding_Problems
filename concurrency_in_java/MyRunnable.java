public class MyRunnable implements Runnable{
    @Override
    public void run(){
        for (int i = 1; i <= 5; i++) {
           System.out.println(Thread.currentThread().getName()+" printing: "+i);
           try {
            Thread.sleep(500);
           } catch (Exception e) {
            System.out.println("Thread interruped: "+e.getMessage());
           }
        }
    }
    
}
