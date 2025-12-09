<div class="ir-problem-heading" bis_skin_checked="1">
    <div class="ir-problem-name" bis_skin_checked="1">Problem 0.1. Путь лягушки</div>
    
    <div class="ir-problem-constraints" bis_skin_checked="1">
        Input file name: <span class="ir-monospace"><em>standard input</em></span><br>
        Output file name: <span class="ir-monospace"><em>standard output</em></span><br>
        
            Time limit: 1 s<br>
        
        
            Memory limit: 256 MB<br>
        
    </div>
</div>

<div class="ir-problem-statement" bis_skin_checked="1">
 <p>В одном очень длинном и узком пруду по кувшинкам
прыгает лягушка. Кувшинки в пруду расположены
в один ряд. Лягушка начинает прыгать с первой
кувшинки ряда и хочет закончить на последней.
Но в силу вредности характера лягушка согласна
прыгать только вперед через одну или через две
кувшинки. Например, с кувшинки номер <span style="white-space: nowrap">1</span>
она может прыгнуть лишь на кувшинки номер <span style="white-space: nowrap">3</span>
и номер <span style="white-space: nowrap">4</span>.</p>
<p>На некоторых кувшинках сидят комарики. А именно,
на <span style="white-space: nowrap"><i>i</i></span>-й кувшинке сидят
<span style="white-space: nowrap"><i>a</i><sub><i>i</i></sub></span> комаров.
Когда лягушка приземляется на кувшинку, она
съедает всех комариков, сидящих на ней. Лягушка
хочет спланировать свой маршрут так, чтобы съесть
как можно больше комаров. Помогите ей: скажите,
какие кувшинки она должна посетить на своем
пути.</p>
<p></p><h2>Input</h2>Первая строка входа
содержит <span style="white-space: nowrap"><i>n</i></span>&nbsp;— число
кувшинок в пруду (<span style="white-space: nowrap">1 ≤ <i>n</i> ≤ 100 000</span>).
Вторая строка содержит <span style="white-space: nowrap"><i>n</i></span>
чисел, разделенных одиночными пробелами. <span style="white-space: nowrap"><i>i</i></span>-е
число сообщает, сколько комаров сидит на <span style="white-space: nowrap"><i>i</i></span>-й
кувшинке (<span style="white-space: nowrap">1 ≤ <i>i</i> ≤ <i>n</i></span>).
Все числа целые, неотрицательные и не превосходят
<span style="white-space: nowrap">1000</span>.<p></p>
<p></p><h2>Output</h2>В первой строке
выведите одно число&nbsp;— максимальное число
комаров, которые может съесть лягушка. Во второй
строке выведите последовательность чисел&nbsp;—
номера тех кувшинок, на которых должна побывать
лягушка, в возрастающем порядке. Если решений
несколько, выведите любое.<p></p>
<p>Если лягушка не может добраться до последней
кувшинки, то выведите одно число <span style="white-space: nowrap">−1</span>.</p>
<p></p><h2>Example</h2> <table class="inputs-outputs">
     <tbody><tr>
         <th>
            standard input
        </th> <th>
            standard output
        </th> 
    </tr> <tr>
        <td>
            6<br>1 100 3 4 1000 0<br>
        </td><td>
            5<br>1 4 6<br>
        </td>
    </tr><tr>
        <td>
            2<br>8 9<br>
        </td><td>
            -1<br>
        </td>
    </tr>
</tbody></table> <p></p> 

</div>