select c.name
    from ratings a
    left join directors b on a.movie_id = b.movie_id
    left join people c on b.person_id = c.id
    where a.rating >= 9 and c.name <> "None";