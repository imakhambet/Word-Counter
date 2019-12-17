<h1> ČVUT FEL PJC – Semestrální práce </h1>

<h3>1. Zadání</h3>
<p>Typický problém s jednoduchou paralelizací. Na vstupu je sada souborů, na výstupu je seřazený výpis obsažených slov a jejich četnost.</p>

<h3>2. Popis implementace</h3>
<p>
Program počítání četnosti slov v sadě souborů je implementovan pomocí prefixověho stromu.

Program parsuje slova ze souborů a vloží je do stromu. Při opakování slova counter u node se zvětší.

Až skončí vložení do stromu, program zavolá metodu, která vratí všechny slova stromu s jejich četnosti ve něm. Pak opdověd' se zapíše do dalšího souboru.
</p>

<h3>3. Vícevlaknový běh programu</h3>
<p>Při vícevlaknovém běhu program používá dva vlakna.
    V prvním vlaknu program parsuje slova ze souborů, které měli lichou pozici na vstupu.
    V druhém vlaknu program parsuje slova ze souborů, které měli sudou pozici na vstupu.
    
    Určitou slabinou použité implementace více vláken je, že program neposkytuje žádné zrychlení při zpracování jednoho souboru.
</p>

<h3>4. Pouštění</h3>
<p> 
Při pouštění program očekavá na určité parametry:
1) "--help" - navod na používání programu
2) "-one inputFiles" - jednovlaknový běh
3) "-two inputFiles" - dvouvlaknový běh

 \* "inputFiles" - je soubor s cestami vstupních souborů z adresáře input
</p>

<h3>5. Vystup</h3>
<p>Po ukončení běhu programu se vypíše čas běhu programu, počet zpracovaných slov, počet uníkatních slov a průměrné časy běhu z historie 
běhu programu pro porovnání. Slova a jejich četnost se zapíše do souburu "output.txt" podle četnosti (od největší). </p>

<h3>6. Testování</h3>
<p>Pro testování je sada s deseti souborů, které obsahují celkem 83038 slova. 

Vystup je možnné zkontrolovat pomocí webové stránky https://www.browserling.com/tools/word-frequency a textu ze souboru "textForTest", která
obsahuje všechny text z deseti souboru adresáře "input".
</p>

<h4>
Průměrný čas pro jednovlaknový běh je 90 ms pro 164 pouštění.
Průměrný čas pro dvouvlaknový běh je 60 ms pro 311 pouštění.
</h4>


