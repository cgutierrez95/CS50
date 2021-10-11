select c.name
    from movies a
    left join stars b on a.id = b.movie_id
    left join people c on b.person_id = c.id
    where a.title = "Toy Story";