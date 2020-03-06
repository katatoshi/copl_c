let plus = fun x -> fun y -> x + y ;;

let minus = fun x -> fun y -> x - y ;;

let times = fun x -> fun y -> x * y ;;

(* リストの長さを返す *)
let rec length = fun xs -> match xs with
    [] -> 0
  | x :: xs' -> 1 + length xs' ;;

let rec range_rec = fun a -> fun b -> fun i ->
  if b < a then []
           else if b < a + i then []
                             else a + i :: range_rec a b (i + 1) ;;

(* a 以上 b 以下の整数のリストを返す *)
let range = fun a -> fun b -> range_rec a b 0 ;;

let rec repeat_rec = fun x -> fun n -> fun i ->
  if n < 1 then []
           else if n < i + 1 then []
                             else x :: repeat_rec x n (i + 1) ;;

(* x を n 回繰り返したリストを返す *)
let repeat = fun x -> fun n -> repeat_rec x n 0 ;;

let rec map = fun f -> fun xs -> match xs with
    [] -> []
  | x :: xs' -> f x :: map f xs' ;;

let rec filter = fun p -> fun xs -> match xs with
    [] -> []
  | x :: xs' -> if p x then x :: filter p xs'
                       else filter p xs' ;;

let rec fold_left = fun f -> fun a -> fun xs -> match xs with
    [] -> a
  | x :: xs' -> fold_left f (f a x) xs' ;;
