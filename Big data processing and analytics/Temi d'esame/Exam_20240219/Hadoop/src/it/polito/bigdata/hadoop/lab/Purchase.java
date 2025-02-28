package it.polito.bigdata.hadoop.lab;

import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.io.WritableUtils;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

public class Purchase implements WritableComparable<Purchase> {
    private String userId; // Identificatore dell'utente
    private String itemId; // Identificatore dell'oggetto acquistato

    // Costruttore vuoto obbligatorio
    public Purchase() {}

    // Costruttore con parametri
    public Purchase(String userId, String itemId) {
        this.userId = userId;
        this.itemId = itemId;
    }

    // Getter e Setter
    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getItemId() {
        return itemId;
    }

    public void setItemId(String itemId) {
        this.itemId = itemId;
    }

    // Serializzazione (scrittura dei dati)
    @Override
    public void write(DataOutput out) throws IOException {
        WritableUtils.writeString(out, userId);
        WritableUtils.writeString(out, itemId);
    }

    // Deserializzazione (lettura dei dati)
    @Override
    public void readFields(DataInput in) throws IOException {
        userId = WritableUtils.readString(in);
        itemId = WritableUtils.readString(in);
    }

    // Implementazione del metodo di confronto
    @Override
    public int compareTo(Purchase other) {
        // Prima confronto su userId
        int result = this.userId.compareTo(other.userId);
        if (result == 0) {
            // Se userId è uguale, confronto su itemId
            return this.itemId.compareTo(other.itemId);
        }
        return result;
    }


    // Override di equals() e hashCode() (coerenza)
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Purchase other = (Purchase) obj;
        return userId.equals(other.userId) && itemId.equals(other.itemId);
    }


    @Override
    public int hashCode() {
        int result = userId.hashCode();
        result = 31 * result + itemId.hashCode();
        return result;
    }

    // Override di toString() per debugging o output leggibile
    @Override
    public String toString() {
        return userId + "\t" + itemId;
    }
}
