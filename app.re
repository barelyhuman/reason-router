open Lib.Route

let routes =
  []
  |> Lib.Route.add(Lib.Route.make("GET", "/hello"))
  |> Lib.Route.add(Lib.Route.make("POST", "/hello"))
  |> Lib.Route.add(Lib.Route.make("GET", "/h"));

switch (Lib.Route.find("/h", "GET", routes)) {
| Some(route) => print_endline(route.pattern)
| None => print_endline("found nothing")
};
