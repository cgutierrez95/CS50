select a.name
    from people a
    where a.id in (select a.person_id
                        from stars a
                        where a.movie_id in (select a.movie_id
                                                from stars a
                                                where a.person_id = (select a.id
                                                    from people a
                                                    where a.name = "Kevin Bacon" and a.birth = 1958))
                        group by a.person_id)
    and a.name <> "Kevin Bacon"
