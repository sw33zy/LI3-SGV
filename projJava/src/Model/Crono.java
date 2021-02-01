package Model;

import static java.lang.System.nanoTime;

public class Crono {

        private long inicio = 0L;
        private long fim = 0L;


        public Crono() {
            this.inicio = 0;
            this.fim = 0;
        }
        public void start() {
            this.fim = 0L;
            this.inicio = nanoTime();
        }

        public double stop() {
            this.fim = nanoTime();
            long elapsedTime = this.fim - this.inicio;
            // segundos
            return elapsedTime / 1.0E09;
        }

        public String getTime() {
            return "" + stop();
        }


        public String getTImeString() {
            return "Elapsed Time: " +getTime() + " s";
        }
    }

