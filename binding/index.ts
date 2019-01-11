import { napiTokenize } from 'binding';

class Startup {
    public static main(): number {
        console.log(napiTokenize(1, ''));
        console.log('Works.');
        return 0;
    }
}

Startup.main();