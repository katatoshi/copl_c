let f = fun x -> x * x ;;
let x = f 2 ;;
2 ;;
x ;;
let rec length = fun xs -> match xs with
    [] -> 0
  | x :: xs' -> 1 + length xs' ;;
let xs = (2 :: 3 :: 5 :: 7 :: []) ;;
length xs ;;
let g = fun f -> fun x -> f (x * x) ;;
g (fun x -> -1 * x) 3 ;;
let h
      =
         2 * 7
   ;;
h ;;
