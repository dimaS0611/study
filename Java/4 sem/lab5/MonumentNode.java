public class MonumentNode {
    String number, type, species, name;

    MonumentNode(String type, String species, String name, String number) {
        this.type = type;
        this.species = species;
        this.name = name;
        this.number = number;
    }

    public String getNumber() { return number; }

    public String getType() {
        return type;
    }

    public String getName() {
        return name;
    }

    public String getSpecies() {
        return species;
    }
}