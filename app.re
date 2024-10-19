open Lib.Route;

let routes =
  Lib.Route.empty()
  |> Lib.Route.add(Lib.Route.make("GET", "/hello"))
  |> Lib.Route.add(Lib.Route.make("GET", "/hello/*"))
  |> Lib.Route.add(Lib.Route.make("GET", "/h"));


let printRoute = (url: string, pattern: string) => url ++ " matched: " ++ pattern;

switch (Lib.Route.find("/hello/1", "GET", routes)) {
| Some(route) =>
  print_endline(printRoute("/hello/1", route.pattern))
| None => print_endline("found nothing")
};

switch (Lib.Route.find("/hello", "GET", routes)) {
| Some(route) => print_endline(printRoute("/hello/1", route.pattern))
| None => print_endline("found nothing")
};
