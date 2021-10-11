select avg(a.energy)
    from songs a
    left join artists b on a.artist_id = b.id
    where b.name = "Drake"