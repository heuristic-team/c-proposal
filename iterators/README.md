# Домашнее задание №N - Итераторы

## Условие

Реализуйте обобщенный интерфейс итератора, используя указатели на функции.

В файле `api.h` определены структуры и функции, которые необходимо реализовать. Каждой из них сопутствует комментарий с описанием ожидаемого функционала. В новом `.c` файле реализуйте требуемый функционал.

Определения структур сделайте в `.c` файле с вашим решением, а так как они не будут известны вне него, возвращайте указатели на выделенные в динамической памяти объекты этих структур в `init`-функциях.

Тестовая система сама считает список, создаст его, используя описанный интерфейс, и исполнит последовательность действий, эквивалентную этим примерам на разных языках:

```python
# Python
l = readList()
for i in l:
  print(i)

mapped = map(lambda x: x + 42, l)
for i in mapped:
  print(i)
```

```rust
// Rust
let l = read_list();
l.iter().foreach(|i| println!("{i}"));
l.iter().map(|i| i + 42).foreach(|i| println!("{i}"));
```

```scala
// Scala
val l = readList()
l foreach println
l map { _ + 42 } foreach println
```

```haskell
-- Haskell
do
  l <- readList
  for_ l print
  for_ (map (+ 42) l) print
```

```OCaml
(* OCaml *)
let list = readList
let print_int = Format.printf "%d\n"
let () =
  List.iter print_int list;
  List.iter print_int (List.map ((+) 42) list)
```

```typescript
// TS/JS
const list = readList()
list.forEach(val => console.log(val))
list.map(val => val + 42).forEach(val => console.log(val))
```

## Пример

### Входные данные

```
5 4 3 2 1 0
```

### Выходные данные

```
1 2 3 4 5
43 44 45 46 47
```
